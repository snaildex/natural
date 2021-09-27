#include "commandPoolImpl.h"
#include "../commandBuffer/commandBufferImpl.h"
#include "../helpers/impl.h"
namespace natural {
	CommandPool::Impl::Impl(Application::Impl* app) {
		m_app = app;
		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = m_app->GetQueueFamilyIndices().GraphicsFamily.value();
		poolInfo.flags = 0;
		ThrowVk(vkCreateCommandPool(m_app->GetVkDevice(), &poolInfo, nullptr, &m_handle));
	}
	CommandPool::Impl::~Impl() {
		vkDestroyCommandPool(m_app->GetVkDevice(), m_handle, nullptr);
	}
	void CommandPool::Impl::CreatePrimaryBuffers(size_t count) {
		CommandBuffer::Impl::Create(m_app, this, m_primaryBuffers, count, VK_COMMAND_BUFFER_LEVEL_PRIMARY);
	}
	void CommandPool::Impl::CreateSecondaryBuffers(size_t count) {
		CommandBuffer::Impl::Create(m_app, this, m_secondaryBuffers, count, VK_COMMAND_BUFFER_LEVEL_SECONDARY);
	}
}