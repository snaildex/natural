#pragma once
#include "application.h"
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
namespace natural {
	class Application::Impl : public Application {
		struct QueueFamilyIndices {
			std::optional<uint32_t> GraphicsFamily;
			std::optional<uint32_t> PresentFamily;
			bool IsComplete() {
				return GraphicsFamily.has_value() && PresentFamily.has_value();
			}
		};

		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR Capabilities;
			std::vector<VkSurfaceFormatKHR> Formats;
			std::vector<VkPresentModeKHR> PresentModes;
		};

		VkInstance m_instance;
		VkDebugUtilsMessengerEXT m_debugMessenger;
		VkPhysicalDevice m_physicalDevice;
		VkDevice m_device;
		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;
		GLFWwindow* m_window;
		VkSurfaceKHR m_surface;
		VkSwapchainKHR m_swapChain;
		std::vector<VkImage> m_swapChainImages;
		VkFormat m_swapChainImageFormat;
		VkExtent2D m_swapChainExtent;
		std::vector<VkImageView> m_swapChainImageViews;

		static bool CheckValidationLayersSupport();
		static std::vector<const char*> GetRequiredExtensions();
		static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void SetupDebugMessenger();
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
		bool IsDeviceSuitable(VkPhysicalDevice device);
		void PickPhysicalDevice();
		void CreateLogicalDevice();
		void CreateSwapChain(int width, int height);
		void CreateImageViews();
		void CreateGraphicsPipeline();

	public:
#ifdef NDEBUG
		static const bool EnableValidationLayers = false;
#else
		static const bool EnableValidationLayers = true;
#endif
		static const std::vector<const char*> ValidationLayers;
		static const std::vector<const char*> DeviceExtensions;

		Impl(int width, int height, const std::string& name, ApplicationListener* listener);
		~Impl();
		void Run() override;

		VkInstance GetVkInstance() const noexcept { return m_instance; }
		VkPhysicalDevice GetVkPhysicalDevise() const noexcept { return m_physicalDevice; }
		VkDevice GetVkDevice() const noexcept { return m_device; }
		VkQueue GetVkGraphicsQueue() const noexcept { return m_graphicsQueue; }
		VkExtent2D GetSwapChainExtent() const noexcept { return m_swapChainExtent; }
		VkFormat GetSwapChainImageFormat() const noexcept { return m_swapChainImageFormat; }
	};
}