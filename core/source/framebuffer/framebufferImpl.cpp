#include "framebufferImpl.h"
namespace natural {
	Framebuffer::Impl::Impl(Application::Impl* app, RenderPass::Impl* renderPass, VkImageView imageView) {
		m_app = app;
		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass->GetHandle();
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = &imageView;
		framebufferInfo.width = app->GetSwapChainExtent().width;
		framebufferInfo.height = app->GetSwapChainExtent().height;
		framebufferInfo.layers = 1;
		ThrowVk(vkCreateFramebuffer(m_app->GetVkDevice(), &framebufferInfo, nullptr, &m_handle));
	}
	Framebuffer::Impl::~Impl() {
		vkDestroyFramebuffer(m_app->GetVkDevice(), m_handle, nullptr);
	}
}