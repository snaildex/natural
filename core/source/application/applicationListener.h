#pragma once
#include "common.h"
#include "../resource/resource.h"
#include "../enums/format.h"
#include "../enums/pipelineStage.h"
#include "../renderPass/renderPassDesc.h"
namespace natural {
	class Application;
	class Resource;
	class RenderPass;
	class RenderPassBuilder;
	class Pipeline;
	class Shader;
	class Framebuffer;
	class CommandPool;
	class Semaphore;
	class Fence;
	class CommandBuffer;
	class ApplicationListener {
		Application* m_app;
		Resource* GetResource(std::function<bool(const Resource*)> predicate);
	public:
		virtual ~ApplicationListener() = default;
		virtual void Start() = 0;
		virtual void Update() = 0;
		friend class Application;
		template<class T> T* GetResource(const std::string& name) {
			return dynamic_cast<T*>(GetResource([&](const Resource* res) {
				if (dynamic_cast<const T*>(res) == nullptr) return false;
				return res->GetName() == name;
			}));
		}
		template<class T> T* GetResource(const std::vector<std::string>& tags) {
			return dynamic_cast<T*>(GetResource([&](const Resource* res) {
				if (dynamic_cast<const T*>(res) == nullptr) return false;
				return res->HasTags(tags);
			}));
		}
		Format GetSwapChainImageFormat();
		glm::uvec2 GetSwapChainExtent();
		uint32_t NextSwapChainImage(Semaphore* semaphore, Fence* fence);
		void BuildRenderPass(std::unique_ptr<RenderPassBuilder>& renderPass);
		void CreatePipeline(std::unique_ptr<Pipeline>& pipeline, Shader* shader, RenderPass* renderPass, int subpass);
		void CreateSwapchainFramebuffers(std::vector<std::unique_ptr<Framebuffer>>& framebuffers, RenderPass* renderPass);
		void CreateCommandPool(std::unique_ptr<CommandPool>& commandPool);
		void CreateSemaphore(std::unique_ptr<Semaphore>& semaphore);
		void CreateFence(std::unique_ptr<Fence>& fence, bool signaled = false);
		void SubmitQueue(const std::vector<std::pair<Semaphore*, PipelineStage>>& waitSemaphores, const std::vector<CommandBuffer*>& commandBuffers, const std::vector<Semaphore*>& signalSemaphores, Fence* signalFence = nullptr);
		bool Wait(const std::vector<Fence*>& fences, bool waitAll = true, uint64_t timeoutNs = UINT64_MAX);
		void Present(const std::vector<Semaphore*>& waitSemaphores, uint32_t imageIndex);
	};
}