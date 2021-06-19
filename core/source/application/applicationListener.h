#pragma once
#include "common.h"
#include "helpers/helpers.h"
#include "../resource/resource.h"
#include "../enums/format.h"
#include "../renderPass/renderPassDesc.h"
namespace natural {
	class Application;
	class Resource;
	class RenderPass;
	class Pipeline;
	class Shader;
	class Framebuffer;
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
		RenderPass* CreateRenderPass(const std::vector<AttachmentDesc>& attachments, const std::vector<SubpassDesc>& subpasses);
		Pipeline* CreatePipeline(Shader* shader, RenderPass* renderPass, int subpass);
		std::vector<Framebuffer*> CreateSwapchainFramebuffers(RenderPass* renderPass);
	};
}