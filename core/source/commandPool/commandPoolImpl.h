#pragma once
#include "commandPool.h"
#include "../application/applicationImpl.h"
#include "../commandBuffer/commandBuffer.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"

namespace natural {
	class CommandPool::Impl : public CommandPool, public HandleBase<VkCommandPool> {
		Application::Impl* m_app;
		std::vector<std::unique_ptr<CommandBuffer>> m_primaryBuffers;
		std::vector<std::unique_ptr<CommandBuffer>> m_secondaryBuffers;
	public:
		Impl(Application::Impl* app);
		~Impl();
		void CreatePrimaryBuffers(size_t count) override;
		void CreateSecondaryBuffers(size_t count) override;
		size_t GetPrimaryBufferCount() const override { return m_primaryBuffers.size(); }
		size_t GetSecondaryBufferCount() const override { return m_secondaryBuffers.size(); }
		CommandBuffer* GetPrimaryBuffer(size_t index) const override { return m_primaryBuffers[index].get(); }
		CommandBuffer* GetSecondaryBuffer(size_t index) const override { return m_secondaryBuffers[index].get(); }
	};
}