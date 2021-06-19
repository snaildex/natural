#pragma once
#include "imageView.h"
#include "../application/applicationImpl.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"

namespace natural {
	class ImageView::Impl : public ImageView, public HandleBase<VkImageView> {
		Application::Impl* m_app;
	public:
		Impl(Application::Impl* app);
		~Impl();
	};
}