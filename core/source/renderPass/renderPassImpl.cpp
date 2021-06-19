#include "renderPassImpl.h"
namespace natural {
	RenderPass::Impl::Impl(
		Application::Impl* app, const std::vector<AttachmentDesc>& attachments, const std::vector<SubpassDesc>& subpasses) {
		m_app = app;
		std::vector<VkAttachmentDescription> vkAttachments;
		std::vector<VkSubpassDescription> vkSubpasses;
		vkAttachments.resize(attachments.size());
		for (int i = 0; i < vkAttachments.size(); ++i) {
			vkAttachments[i] = {};
			vkAttachments[i].format = (VkFormat)(int)attachments[i].Format;
			vkAttachments[i].samples = VK_SAMPLE_COUNT_1_BIT;
			vkAttachments[i].loadOp = (VkAttachmentLoadOp)(int)attachments[i].LoadOp;
			vkAttachments[i].storeOp = (VkAttachmentStoreOp)(int)attachments[i].StoreOp;
			vkAttachments[i].stencilLoadOp = (VkAttachmentLoadOp)(int)attachments[i].StencilLoadOp;
			vkAttachments[i].stencilStoreOp = (VkAttachmentStoreOp)(int)attachments[i].StencilStoreOp;
			vkAttachments[i].initialLayout = (VkImageLayout)(int)attachments[i].InitialLayout;
			vkAttachments[i].finalLayout = (VkImageLayout)(int)attachments[i].FinalLayout;
		}
		vkSubpasses.resize(subpasses.size());
		for (int i = 0; i < vkSubpasses.size(); ++i) {
			vkSubpasses[i] = {};
			vkSubpasses[i].pipelineBindPoint = (VkPipelineBindPoint)(int)subpasses[i].PipelineBindPoint;
			vkSubpasses[i].colorAttachmentCount = subpasses[i].Attahcments.size();
			auto atRef = new VkAttachmentReference[vkSubpasses[i].colorAttachmentCount];
			for (int j = 0; j < subpasses[i].Attahcments.size(); ++j) {
				atRef[j] = {};
				atRef[j].attachment = subpasses[i].Attahcments[j].Index;
				atRef[j].layout = (VkImageLayout)(int)subpasses[i].Attahcments[j].Layout;
			}
			vkSubpasses[i].pColorAttachments = atRef;
		}
		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = vkAttachments.size();
		renderPassInfo.pAttachments = vkAttachments.data();
		renderPassInfo.subpassCount = vkSubpasses.size();
		renderPassInfo.pSubpasses = vkSubpasses.data();
		ThrowVk(vkCreateRenderPass(m_app->GetVkDevice(), &renderPassInfo, nullptr, &m_handle));
		for (int i = 0; i < vkSubpasses.size(); ++i) delete[] vkSubpasses[i].pColorAttachments;
	}
	RenderPass::Impl::~Impl() {
		vkDestroyRenderPass(m_app->GetVkDevice(), m_handle, nullptr);
	}
}