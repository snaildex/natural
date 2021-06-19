#pragma once
#include "../common.h"
#include "../helpers/helpers.h"
#include "../enums/format.h"
#include "../enums/attachmentLoadStoreOp.h"
#include "../enums/imageLayout.h"
#include "../enums/pipelineBindPoint.h"
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
}