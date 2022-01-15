#pragma once
#include "../common.h"
#include "../enums/format.h"
#include "../enums/attachmentLoadStoreOp.h"
#include "../enums/imageLayout.h"
#include "../enums/pipelineBindPoint.h"
#include "../enums/pipelineStage.h"
#include "../enums/access.h"
#include "../enums/dependency.h"
namespace natural {
	struct AttachmentDesc {
		Format Format;
		AttachmentLoadOp LoadOp;
		AttachmentStoreOp StoreOp;
		AttachmentLoadOp StencilLoadOp;
		AttachmentStoreOp StencilStoreOp;
		ImageLayout InitialLayout;
		ImageLayout FinalLayout;
	};
	struct ColorAttachmentRef {
		uint32_t Index;
		ImageLayout Layout;
	};
	struct SubpassDesc {
		PipelineBindPoint PipelineBindPoint;
		std::vector<ColorAttachmentRef> Attahcments;
	};
	struct SubpassDependencyDesc {
		uint32_t SrcSubpass;
		uint32_t DstSubpass;
		PipelineStage SrcStageMask;
		PipelineStage DstStageMask;
		Access SrcAccessMask;
		Access DstAccessMask;
		Dependency DependencyFlags;
	};
	extern uint32_t SubpassExternal;
}