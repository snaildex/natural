#include "pipelineImpl.h"
#include "../helpers/impl.h"
#include "../resource/shader/shaderImpl.h"
#include "../renderPass/renderPassImpl.h"
namespace natural {
	Pipeline::Impl::Impl(Application::Impl* app, Shader* shader, RenderPass* renderPass, int subpass)
	{
		m_app = app;
		shader->EnsureLoaded();
		auto modules = impl(shader)->GetShaderModules();
		m_shaderStages.resize(modules.size());
		int i = 0;
		for (auto& sm : modules) {
			VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
			vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			vertShaderStageInfo.stage = (VkShaderStageFlagBits)sm.first;
			vertShaderStageInfo.module = sm.second;
			vertShaderStageInfo.pName = "main";
			m_shaderStages[i++] = vertShaderStageInfo;
		}

		m_vertexInputInfo = {};
		m_vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		m_vertexInputInfo.vertexBindingDescriptionCount = 0;
		m_vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
		m_vertexInputInfo.vertexAttributeDescriptionCount = 0;
		m_vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

		m_inputAssembly = {};
		m_inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		m_inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		m_inputAssembly.primitiveRestartEnable = VK_FALSE;

		m_viewports.resize(1);
		m_viewports[0] = {};
		m_viewports[0].x = 0.0f;
		m_viewports[0].y = 0.0f;
		m_viewports[0].width = (float)m_app->GetSwapChainExtent().width;
		m_viewports[0].height = (float)m_app->GetSwapChainExtent().height;
		m_viewports[0].minDepth = 0.0f;
		m_viewports[0].maxDepth = 1.0f;
		m_scissors.resize(1);
		m_scissors[0] = {};
		m_scissors[0].offset = { 0, 0 };
		m_scissors[0].extent = m_app->GetSwapChainExtent();
		m_viewportState = {};
		m_viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		m_viewportState.viewportCount = m_viewports.size();
		m_viewportState.pViewports = m_viewports.data();
		m_viewportState.scissorCount = m_scissors.size();
		m_viewportState.pScissors = m_scissors.data();

		m_rasterizer = {};
		m_rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		m_rasterizer.depthClampEnable = VK_FALSE;
		m_rasterizer.rasterizerDiscardEnable = VK_FALSE;
		m_rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		m_rasterizer.lineWidth = 1.0f;
		m_rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		m_rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
		m_rasterizer.depthBiasEnable = VK_FALSE;

		m_multisampling = {};
		m_multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		m_multisampling.sampleShadingEnable = VK_FALSE;
		m_multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		m_colorBlendAttachments.resize(1);
		m_colorBlendAttachments[0] = {};
		m_colorBlendAttachments[0].colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		m_colorBlendAttachments[0].blendEnable = VK_FALSE;

		m_colorBlending = {};
		m_colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		m_colorBlending.logicOpEnable = VK_FALSE;
		m_colorBlending.attachmentCount = m_colorBlendAttachments.size();
		m_colorBlending.pAttachments = m_colorBlendAttachments.data();

		m_dynamicStates = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_LINE_WIDTH
		};

		m_dynamicStateInfo = {};
		m_dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		m_dynamicStateInfo.dynamicStateCount = m_dynamicStates.size();
		m_dynamicStateInfo.pDynamicStates = m_dynamicStates.data();

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		ThrowVk(vkCreatePipelineLayout(m_app->GetVkDevice(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout));

		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = m_shaderStages.size();
		pipelineInfo.pStages = m_shaderStages.data();
		pipelineInfo.pVertexInputState = &m_vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &m_inputAssembly;
		pipelineInfo.pViewportState = &m_viewportState;
		pipelineInfo.pRasterizationState = &m_rasterizer;
		pipelineInfo.pMultisampleState = &m_multisampling;
		pipelineInfo.pColorBlendState = &m_colorBlending;
		pipelineInfo.layout = m_pipelineLayout;
		pipelineInfo.renderPass = impl(renderPass)->GetHandle();
		pipelineInfo.subpass = subpass;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineInfo.basePipelineIndex = -1;
		ThrowVk(vkCreateGraphicsPipelines(m_app->GetVkDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_handle));
	}

	Pipeline::Impl::~Impl()
	{
		vkDestroyPipelineLayout(m_app->GetVkDevice(), m_pipelineLayout, nullptr);
		vkDestroyPipeline(m_app->GetVkDevice(), m_handle, nullptr);
	}
}