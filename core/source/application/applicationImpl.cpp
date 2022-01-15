#include "applicationImpl.h"
#include "../helpers/impl.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>
#include "../helpers/vulkanHelpers.h"
#include "../resource/resourceBuilderMap.h"

namespace natural {
	std::vector<const char*> Application::Impl::GetRequiredExtensions() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		if (EnableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}
		return extensions;
	}

	Application::Impl::Impl(int width, int height, const std::string& name, ApplicationListener* listener) {
		listener->m_app = this;
		m_listener.reset(listener);

		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_window = glfwCreateWindow(width, height, name.data(), nullptr, nullptr);

		CheckValidationLayersSupport();
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = name.data();
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "natural";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		if (EnableValidationLayers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size());
			createInfo.ppEnabledLayerNames = ValidationLayers.data();
			PopulateDebugMessengerCreateInfo(debugCreateInfo);
			createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
		}
		else {
			createInfo.enabledLayerCount = 0;
		}
		auto requiredExtensions = GetRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
		createInfo.ppEnabledExtensionNames = requiredExtensions.data();

		ThrowVk(vkCreateInstance(&createInfo, nullptr, &m_instance));

		glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface);

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
		{
			Log("supported vulkan extensions:");
			LogIndent();
			for (const auto& extension : extensions) Log("%s", extension.extensionName);
		}
		SetupDebugMessenger();
		PickPhysicalDevice();
		CreateLogicalDevice();
		CreateSwapChain(width, height);
		CreateImageViews();
		ScanResources();
		m_listener->Start();
	}

	void Application::ScanResources() {
		RegisterResourceBuilders();
		Log("Scanning resources...");
		LogIndent();
		auto configs = ScanFiles(".json");
		for (const std::filesystem::path& config : configs) {
			std::ifstream configFile(config);
			std::filesystem::path cpath = std::filesystem::current_path();
			std::filesystem::current_path(config.parent_path());
			json conf = json::parse(configFile);
			Log("Scanning %s", config.string().data());
			if (conf.is_array()) {
				for (auto& child : conf)
					if (Resource* r = BuildResource(impl(this), child)) AddResource(r);
			}
			else
				if (Resource* r = BuildResource(impl(this), conf)) AddResource(r);
			std::filesystem::current_path(cpath);
			configFile.close();
		}
	}

	Application::Impl::~Impl() {
		m_listener.reset();
		for (std::unique_ptr<Resource>& r : m_resources) {
			r->StartUnloading();
			r->WaitForUnload();
			r.reset();
		}
		for (auto imageView : m_swapChainImageViews)
			vkDestroyImageView(m_device, imageView, nullptr);
		vkDestroySwapchainKHR(m_device, m_swapChain, nullptr);
		vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
		vkDestroyDevice(m_device, nullptr);
		if (EnableValidationLayers)
			DestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);
		vkDestroyInstance(m_instance, nullptr);
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void Application::Impl::Run()
	{
		while (!glfwWindowShouldClose(m_window)) {
			glfwPollEvents();
			m_listener->Update();
		}
		ThrowVk(vkDeviceWaitIdle(m_device));
	}

	Application* Application::Create(int width, int height, const std::string& name, ApplicationListener* listener)
	{
		return new Application::Impl(width, height, name, listener);
	}
}