#include "semaphoreImpl.h"
namespace natural {
	Semaphore::Impl::Impl(Application::Impl* app) {
		m_app = app;
		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		ThrowVk(vkCreateSemaphore(m_app->GetVkDevice(), &semaphoreInfo, nullptr, &m_handle));
	}
	Semaphore::Impl::~Impl() {
		vkDestroySemaphore(m_app->GetVkDevice(), m_handle, nullptr);
	}
}