#pragma once
#include "renderPassBuilder.h"
#include "../application/applicationImpl.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"

namespace natural {
	class RenderPassBuilder::Impl : public RenderPassBuilder {
		Application::Impl* m_app;
		std::vector<AttachmentDesc> m_attachments;
		std::vector<SubpassDesc> m_subpasses;
		std::vector<SubpassDependencyDesc> m_subpassDeps;
	public:
		Impl(Application::Impl* app);
		void AddAttachment(const AttachmentDesc& attachment) override { m_attachments.push_back(attachment); }
		void AddSubpass(const SubpassDesc& subpass) override { m_subpasses.push_back(subpass); }
		void AddSubpassDependency(const SubpassDependencyDesc& subpassDep) override { m_subpassDeps.push_back(subpassDep); }
		AttachmentDesc& Attachment(int index) override { return m_attachments[index]; }
		SubpassDesc& Subpass(int index) override { return m_subpasses[index]; }
		SubpassDependencyDesc& SubpassDependency(int index) override { return m_subpassDeps[index]; }
		void Build(std::unique_ptr<RenderPass>& renderPass) override;
	};
}