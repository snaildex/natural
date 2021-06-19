#pragma once
#include "renderPass.h"
#include "../application/applicationImpl.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"

namespace natural {
	class RenderPass::Impl : public RenderPass, public HandleBase<VkRenderPass> {
		Application::Impl* m_app;
	public:
		Impl(Application::Impl* app, const std::vector<AttachmentDesc>& attachments, const std::vector<SubpassDesc>& subpasses);
		~Impl();
	};
}