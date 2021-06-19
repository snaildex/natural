#include "applicationListener.h"
#include "application.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"
#include "../helpers/impl.h"
#include "../renderPass/renderPassImpl.h"
#include "../pipeline/pipelineImpl.h"
#include "../framebuffer/framebufferImpl.h"
namespace natural {
	Resource* ApplicationListener::GetResource(std::function<bool(const Resource*)> predicate) {
		return m_app->GetResource(predicate);
	}
	RenderPass* ApplicationListener::CreateRenderPass(
		const std::vector<AttachmentDesc>& attachments, const std::vector<SubpassDesc>& subpasses) {
		return new RenderPass::Impl(impl(m_app), attachments, subpasses);
	}
	Format ApplicationListener::GetSwapChainImageFormat() {
		return m_app->GetSwapChainImageFormat();
	}
	Pipeline* ApplicationListener::CreatePipeline(Shader* shader, RenderPass* renderPass, int subpass) {
		return new Pipeline::Impl(impl(m_app), shader, renderPass, subpass);
	}
	std::vector<Framebuffer*> CreateSwapchainFramebuffers(RenderPass* renderPass) {

	}
}