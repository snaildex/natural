#include "renderPassBuilderImpl.h"
#include "renderPassImpl.h"
namespace natural {
	RenderPassBuilder::Impl::Impl(Application::Impl* app) {
		m_app = app;
	}
	void RenderPassBuilder::Impl::Build(std::unique_ptr<RenderPass>& renderPass) {
		std::vector<VkAttachmentDescription> vkAttachments;
		std::vector<VkSubpassDescription> vkSubpasses;
		std::vector<VkSubpassDependency> vkSubpassDeps;
		vkAttachments.resize(m_attachments.size());
		for (int i = 0; i < vkAttachments.size(); ++i) {
			vkAttachments[i] = {};
			vkAttachments[i].format = (VkFormat)(int)m_attachments[i].Format;
			vkAttachments[i].samples = VK_SAMPLE_COUNT_1_BIT;
			vkAttachments[i].loadOp = (VkAttachmentLoadOp)(int)m_attachments[i].LoadOp;
			vkAttachments[i].storeOp = (VkAttachmentStoreOp)(int)m_attachments[i].StoreOp;
			vkAttachments[i].stencilLoadOp = (VkAttachmentLoadOp)(int)m_attachments[i].StencilLoadOp;
			vkAttachments[i].stencilStoreOp = (VkAttachmentStoreOp)(int)m_attachments[i].StencilStoreOp;
			vkAttachments[i].initialLayout = (VkImageLayout)(int)m_attachments[i].InitialLayout;
			vkAttachments[i].finalLayout = (VkImageLayout)(int)m_attachments[i].FinalLayout;
		}
		vkSubpasses.resize(m_subpasses.size());
		for (int i = 0; i < vkSubpasses.size(); ++i) {
			vkSubpasses[i] = {};
			vkSubpasses[i].pipelineBindPoint = (VkPipelineBindPoint)(int)m_subpasses[i].PipelineBindPoint;
			vkSubpasses[i].colorAttachmentCount = m_subpasses[i].Attahcments.size();
			auto atRef = new VkAttachmentReference[vkSubpasses[i].colorAttachmentCount];
			for (int j = 0; j < m_subpasses[i].Attahcments.size(); ++j) {
				atRef[j] = {};
				atRef[j].attachment = m_subpasses[i].Attahcments[j].Index;
				atRef[j].layout = (VkImageLayout)(int)m_subpasses[i].Attahcments[j].Layout;
			}
			vkSubpasses[i].pColorAttachments = atRef;
		}
		vkSubpassDeps.resize(m_subpassDeps.size());
		for (int i = 0; i < vkSubpassDeps.size(); ++i) {
			vkSubpassDeps[i] = {};
			vkSubpassDeps[i].dependencyFlags = m_subpassDeps[i].DependencyFlags;
			vkSubpassDeps[i].dstAccessMask = m_subpassDeps[i].DstAccessMask;
			vkSubpassDeps[i].dstStageMask = m_subpassDeps[i].DstStageMask;
			vkSubpassDeps[i].dstSubpass = m_subpassDeps[i].DstSubpass;
			vkSubpassDeps[i].srcAccessMask = m_subpassDeps[i].SrcAccessMask;
			vkSubpassDeps[i].srcStageMask = m_subpassDeps[i].SrcStageMask;
			vkSubpassDeps[i].srcSubpass = m_subpassDeps[i].SrcSubpass;
		}
		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = vkAttachments.size();
		renderPassInfo.pAttachments = vkAttachments.data();
		renderPassInfo.subpassCount = vkSubpasses.size();
		renderPassInfo.pSubpasses = vkSubpasses.data();
		renderPassInfo.dependencyCount = vkSubpassDeps.size();
		renderPassInfo.pDependencies = vkSubpassDeps.data();
		renderPass.reset(new RenderPass::Impl(m_app, renderPassInfo));
		for (int i = 0; i < vkSubpasses.size(); ++i) delete[] vkSubpasses[i].pColorAttachments;
	}
}