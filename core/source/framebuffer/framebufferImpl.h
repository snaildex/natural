#pragma once
#include "framebuffer.h"
#include "../application/applicationImpl.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"

namespace natural {
	class Framebuffer::Impl : public Framebuffer, public HandleBase<VkRenderPass> {
		Application::Impl* m_app;
	public:
		Impl(Application::Impl* app);
		~Impl();
	};
}