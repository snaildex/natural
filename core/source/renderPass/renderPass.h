#pragma once
#include "../common.h"
#include "../helpers/helpers.h"
#include "../enums/format.h"
#include "../enums/attachmentLoadStoreOp.h"
#include "../enums/imageLayout.h"
#include "renderPassDesc.h"
namespace natural {
	class RenderPass {
	public:
		virtual ~RenderPass() = default;
		class Impl;
	};
}