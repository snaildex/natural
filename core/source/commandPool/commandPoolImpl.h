#pragma once
#include "commandPool.h"
#include "../application/applicationImpl.h"
#include "../commandBuffer/commandBuffer.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"

namespace natural {
	class CommandPool::Impl : public CommandPool, public HandleBase<VkCommandPool> {
		Application::Impl* m_app;
	public:
		Impl(Application::Impl* app);
		~Impl();
		void CreatePrimaryBuffer(std::unique_ptr<CommandBuffer>& buffer) override;
		void CreateSecondaryBuffer(std::unique_ptr<CommandBuffer>& buffer) override;
	};
}