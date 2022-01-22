#pragma once
#include "commandBuffer.h"
#include "../commandPool/commandPoolImpl.h"
#include "../application/applicationImpl.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"

namespace natural {
	class CommandBuffer::Impl : public CommandBuffer, public HandleBase<VkCommandBuffer> {
		Application::Impl* m_app;
		CommandPool::Impl* m_pool;
	public:
		Impl(Application::Impl* app, CommandPool::Impl* pool, VkCommandBufferLevel level);
		~Impl();
		void Begin(CommandBufferUsage usage = 0) override;
		void End() override;
		void CmdBeginRenderPass(
			RenderPass* renderPass,
			Framebuffer* framebuffer,
			const glm::ivec2& offset,
			const glm::uvec2& extent,
			const std::vector<glm::fvec4>& clearValues,
			SubpassContents contents = SubpassContents::Inline
		) override;
		void CmdEndRenderPass() override;
		void CmdBindPipeline(Pipeline* pipeline, PipelineBindPoint bindPoint) override;
		void CmdDraw(unsigned int vertexCount, unsigned int instanceCount, unsigned int firstVertex, unsigned int firstInstance) override;
	};
}