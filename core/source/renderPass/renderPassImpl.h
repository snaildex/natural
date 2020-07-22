#pragma once
#include "renderPass.h"
#include "../application/applicationImpl.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"
namespace natural {
	class RenderPass::Impl : public RenderPass {
		Application::Impl* m_app;
		VkRenderPass m_renderPass;
	public:
		Impl(Application::Impl* app);
		~Impl();
	};
}