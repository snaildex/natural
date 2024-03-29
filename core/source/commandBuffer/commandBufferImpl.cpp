#include "commandBufferImpl.h"
#include"../helpers/impl.h"
#include "../renderPass/renderPassImpl.h"
#include "../framebuffer/framebufferImpl.h"
#include "../pipeline/pipelineImpl.h"
namespace natural {
	CommandBuffer::Impl::Impl(Application::Impl* app, CommandPool::Impl* pool, VkCommandBufferLevel level) {
		m_app = app;
		m_pool = pool;
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = pool->GetHandle();
		allocInfo.level = level;
		allocInfo.commandBufferCount = 1;
		ThrowVk(vkAllocateCommandBuffers(app->GetVkDevice(), &allocInfo, &m_handle));
	}
	CommandBuffer::Impl::~Impl() {
		vkFreeCommandBuffers(m_app->GetVkDevice(), m_pool->GetHandle(), 1, &m_handle);
	}
	void CommandBuffer::Impl::Begin(CommandBufferUsage usage) {
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = usage;
		beginInfo.pInheritanceInfo = nullptr;
		ThrowVk(vkBeginCommandBuffer(m_handle, &beginInfo));
	}
	void CommandBuffer::Impl::End() {
		ThrowVk(vkEndCommandBuffer(m_handle));
	}
	void CommandBuffer::Impl::CmdBeginRenderPass(
		RenderPass* renderPass,
		Framebuffer* framebuffer,
		const glm::ivec2& offset,
		const glm::uvec2& extent,
		const std::vector<glm::fvec4>& clearValues,
		SubpassContents contents
	) {
		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = impl(renderPass)->GetHandle();
		renderPassInfo.framebuffer = impl(framebuffer)->GetHandle();
		renderPassInfo.renderArea.offset = { offset.x, offset.y };
		renderPassInfo.renderArea.extent = { extent.x,extent.y };
		std::vector<VkClearValue> clears;
		clears.resize(clearValues.size());
		for (int i = 0; i < clears.size(); ++i) clears[i] = { clearValues[i].r, clearValues[i].g, clearValues[i].b, clearValues[i].a };
		renderPassInfo.clearValueCount = clears.size();
		renderPassInfo.pClearValues = clears.data();
		vkCmdBeginRenderPass(GetHandle(), &renderPassInfo, (VkSubpassContents)((int)contents));
	}
	void CommandBuffer::Impl::CmdEndRenderPass() {
		vkCmdEndRenderPass(GetHandle());
	}
	void CommandBuffer::Impl::CmdBindPipeline(Pipeline* pipeline, PipelineBindPoint bindPoint) {
		vkCmdBindPipeline(GetHandle(), (VkPipelineBindPoint)((int)bindPoint), impl(pipeline)->GetHandle());
	}
	void CommandBuffer::Impl::CmdDraw(unsigned int vertexCount, unsigned int instanceCount, unsigned int firstVertex, unsigned int firstInstance) {
		vkCmdDraw(GetHandle(), vertexCount, instanceCount, firstVertex, firstInstance);
	}
}