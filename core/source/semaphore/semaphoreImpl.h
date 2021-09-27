#pragma once
#include "semaphore.h"
#include "../application/applicationImpl.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"

namespace natural {
	class Semaphore::Impl : public Semaphore, public HandleBase<VkSemaphore> {
		Application::Impl* m_app;
	public:
		Impl(Application::Impl* app);
		~Impl();
	};
}