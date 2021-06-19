#pragma once
#include "pipeline.h"
#include "../application/applicationImpl.h"
#include <vulkan/vulkan.h>
#include "../helpers/vulkanHelpers.h"

namespace natural {
	class Pipeline::Impl : public Pipeline, public HandleBase<VkPipeline> {
		Application::Impl* m_app;
		std::vector<VkPipelineShaderStageCreateInfo> m_shaderStages;
		VkPipelineVertexInputStateCreateInfo m_vertexInputInfo;
		VkPipelineInputAssemblyStateCreateInfo m_inputAssembly;
		std::vector<VkViewport> m_viewports;
		std::vector<VkRect2D> m_scissors;
		VkPipelineViewportStateCreateInfo m_viewportState;
		VkPipelineRasterizationStateCreateInfo m_rasterizer;
		VkPipelineMultisampleStateCreateInfo m_multisampling;
		std::vector<VkPipelineColorBlendAttachmentState> m_colorBlendAttachments;
		VkPipelineColorBlendStateCreateInfo m_colorBlending;
		std::vector<VkDynamicState> m_dynamicStates;
		VkPipelineDynamicStateCreateInfo m_dynamicStateInfo;
		VkPipelineLayout m_pipelineLayout;
	public:
		Impl(Application::Impl* app, Shader* shader, RenderPass* renderPass, int subpass);
		~Impl();
	};
}