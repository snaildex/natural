#include "applicationListener.h"
#include "application.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"
#include "../helpers/impl.h"
#include "../renderPass/renderPassImpl.h"
#include "../renderPass/renderPassBuilderImpl.h"
#include "../pipeline/pipelineImpl.h"
#include "../framebuffer/framebufferImpl.h"
#include "../commandPool/commandPoolImpl.h"
#include "../semaphore/semaphoreImpl.h"
#include "../fence/fenceImpl.h"
#include "../commandBuffer/commandBufferImpl.h"
namespace natural {
	Resource* ApplicationListener::GetResource(std::function<bool(const Resource*)> predicate) {
		return m_app->GetResource(predicate);
	}
	void ApplicationListener::BuildRenderPass(std::unique_ptr<RenderPassBuilder>& renderPass) {
		renderPass.reset(new RenderPassBuilder::Impl(impl(m_app)));
	}
	Format ApplicationListener::GetSwapChainImageFormat() {
		return m_app->GetSwapChainImageFormat();
	}
	uint32_t ApplicationListener::NextSwapChainImage(Semaphore* semaphore) {
		uint32_t imageIndex = -1;
		ThrowVk(vkAcquireNextImageKHR(impl(m_app)->GetVkDevice(), impl(m_app)->GetSwapChain(), UINT64_MAX, semaphore ? impl(semaphore)->GetHandle() : VK_NULL_HANDLE, VK_NULL_HANDLE, &imageIndex));
		return imageIndex;
	}
	void ApplicationListener::CreatePipeline(std::unique_ptr<Pipeline>& pipeline, Shader* shader, RenderPass* renderPass, int subpass) {
		pipeline.reset(new Pipeline::Impl(impl(m_app), shader, renderPass, subpass));
	}
	void ApplicationListener::CreateSwapchainFramebuffers(std::vector<std::unique_ptr<Framebuffer>>& framebuffers, RenderPass* renderPass) {
		framebuffers.resize(impl(m_app)->GetSwapChainImageViews().size());
		for (int i = 0; i < impl(m_app)->GetSwapChainImageViews().size(); i++)
			framebuffers[i].reset(new Framebuffer::Impl(impl(m_app), impl(renderPass), impl(m_app)->GetSwapChainImageViews()[i]));
	}
	void ApplicationListener::CreateCommandPool(std::unique_ptr<CommandPool>& commandPool) {
		commandPool.reset(new CommandPool::Impl(impl(m_app)));
	}
	void ApplicationListener::CreateSemaphore(std::unique_ptr<Semaphore>& semaphore) {
		semaphore.reset(new Semaphore::Impl(impl(m_app)));
	}
	void ApplicationListener::CreateFence(std::unique_ptr<Fence>& fence, bool signaled) {
		fence.reset(new Fence::Impl(impl(m_app), signaled));
	}
	void ApplicationListener::SubmitQueue(const std::vector<std::pair<Semaphore*, PipelineStage>>& waitSemaphores, const std::vector<CommandBuffer*>& commandBuffers, const std::vector<Semaphore*>& signalSemaphores, Fence* signalFence) {
		std::vector<VkSemaphore> vkWaitSem;
		std::vector<VkPipelineStageFlags> vkWaitStages;
		std::vector<VkCommandBuffer> vkCmdBufs;
		std::vector<VkSemaphore> vkSigSem;
		vkWaitSem.resize(waitSemaphores.size());
		vkWaitStages.resize(waitSemaphores.size());
		for (int i = 0; i < vkWaitSem.size(); ++i) {
			vkWaitSem[i] = impl(waitSemaphores[i].first)->GetHandle();
			vkWaitStages[i] = waitSemaphores[i].second;
		}
		CollectVkHandles(vkCmdBufs, commandBuffers);
		CollectVkHandles(vkSigSem, signalSemaphores);
		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.pWaitSemaphores = vkWaitSem.data();
		submitInfo.waitSemaphoreCount = vkWaitSem.size();
		submitInfo.pWaitDstStageMask = vkWaitStages.data();
		submitInfo.pSignalSemaphores = vkSigSem.data();
		submitInfo.signalSemaphoreCount = vkSigSem.size();
		ThrowVk(vkQueueSubmit(impl(m_app)->GetVkGraphicsQueue(), 1, &submitInfo, signalFence ? impl(signalFence)->GetHandle() : VK_NULL_HANDLE));
	}
	bool ApplicationListener::Wait(const std::vector<Fence*>& fences, bool waitAll, uint64_t timeoutNs) {
		std::vector<VkFence> vkFen;
		CollectVkHandles(vkFen, fences);
		return ThrowVk(vkWaitForFences(impl(m_app)->GetVkDevice(), vkFen.size(), vkFen.data(), waitAll, timeoutNs)) == VK_SUCCESS;
	}
	void ApplicationListener::Present(const std::vector<Semaphore*>& waitSemaphores, uint32_t imageIndex) {
		std::vector<VkSemaphore> vkWairSem;
		CollectVkHandles(vkWairSem, waitSemaphores);
		VkSwapchainKHR swapChains[] = { impl(m_app)->GetSwapChain() };
		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = vkWairSem.size();
		presentInfo.pWaitSemaphores = vkWairSem.data();
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;
		presentInfo.pImageIndices = &imageIndex;
		presentInfo.pResults = nullptr;
		ThrowVk(vkQueuePresentKHR(impl(m_app)->GetVkPresentQueue(), &presentInfo));
	}
}