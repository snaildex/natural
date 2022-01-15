#pragma once
#include "../enums/commandBuffer.h"
#include "../enums/pipelineBindPoint.h"
#include "../common.h"
namespace natural {
	class RenderPass;
	class Framebuffer;
	class Pipeline;
	class CommandBuffer {
	public:
		virtual ~CommandBuffer() = default;
		class Impl;
		virtual void Begin(CommandBufferUsage usage = 0) = 0;
		virtual void End() = 0;
		virtual void CmdBeginRenderPass(
			RenderPass* renderPass,
			Framebuffer* framebuffer,
			const glm::ivec2& offset,
			const glm::uvec2& extent,
			const std::vector<glm::fvec4>& clearValues,
			SubpassContents contents = SubpassContents::Inline
		) = 0;
		virtual void CmdEndRenderPass() = 0;
		virtual void CmdBindPipeline(Pipeline* pipeline, PipelineBindPoint bindPoint) = 0;
		virtual void CmdDraw(unsigned int vertexCount, unsigned int instanceCount, unsigned int firstVertex, unsigned int firstInstance) = 0;
	};
}