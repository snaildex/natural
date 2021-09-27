#pragma once
#include "fence.h"
#include "../application/applicationImpl.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"

namespace natural {
	class Fence::Impl : public Fence, public HandleBase<VkFence> {
		Application::Impl* m_app;
	public:
		Impl(Application::Impl* app, bool signaled);
		~Impl();
		void Reset() override;
		bool IsSignaled() override;
	};
}