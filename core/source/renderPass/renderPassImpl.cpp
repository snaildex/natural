#include "renderPassImpl.h"
namespace natural {
	RenderPass::Impl::Impl(Application::Impl* app, const VkRenderPassCreateInfo& createInfo) {
		m_app = app;
		ThrowVk(vkCreateRenderPass(m_app->GetVkDevice(), &createInfo, nullptr, &m_handle));
	}
	RenderPass::Impl::~Impl() {
		vkDestroyRenderPass(m_app->GetVkDevice(), m_handle, nullptr);
	}
}