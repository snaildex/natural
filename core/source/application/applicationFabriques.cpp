#include "applicationImpl.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"
#include "../helpers/impl.h"
#include "../renderPass/renderPassImpl.h"
namespace natural {
	RenderPass* Application::CreateRenderPass() {
		return new RenderPass::Impl(impl(this));
	}
}