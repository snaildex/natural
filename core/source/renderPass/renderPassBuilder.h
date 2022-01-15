#pragma once
#include "../common.h"
#include "../enums/format.h"
#include "../enums/attachmentLoadStoreOp.h"
#include "../enums/imageLayout.h"
#include "renderPass.h"
#include "renderPassDesc.h"
namespace natural {
	class RenderPassBuilder {
	public:
		virtual ~RenderPassBuilder() = default;
		class Impl;
		virtual void AddAttachment(const AttachmentDesc& attachment) = 0;
		virtual void AddSubpass(const SubpassDesc& subpass) = 0;
		virtual void AddSubpassDependency(const SubpassDependencyDesc& subpassDep) = 0;
		virtual AttachmentDesc& Attachment(int index) = 0;
		virtual SubpassDesc& Subpass(int index) = 0;
		virtual SubpassDependencyDesc& SubpassDependency(int index) = 0;
		virtual void Build(std::unique_ptr<RenderPass>& renderPass) = 0;
	};
}