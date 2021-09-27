#include "fenceImpl.h"
namespace natural {
	Fence::Impl::Impl(Application::Impl* app, bool signaled) {
		m_app = app;
		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		if (signaled) fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
		ThrowVk(vkCreateFence(m_app->GetVkDevice(), &fenceInfo, nullptr, &m_handle));
	}
	Fence::Impl::~Impl() {
		vkDestroyFence(m_app->GetVkDevice(), m_handle, nullptr);
	}
	void Fence::Impl::Reset() {
		ThrowVk(vkResetFences(m_app->GetVkDevice(), 1, &m_handle));
	}
	bool Fence::Impl::IsSignaled() {
		return ThrowVk(vkGetFenceStatus(m_app->GetVkDevice(), m_handle)) == VK_SUCCESS;
	}
}