#include "pipelineImpl.h"
namespace natural {
	std::map<std::string, Pipeline::Impl::Stage> Pipeline::Impl::m_stageNames{
		{"vert",Pipeline::Impl::Stage::Vertex},
		{"tesc",Pipeline::Impl::Stage::TessCtrl},
		{"tese",Pipeline::Impl::Stage::TessEval},
		{"geom",Pipeline::Impl::Stage::Geometry},
		{"frag",Pipeline::Impl::Stage::Fragment},
		{"comp",Pipeline::Impl::Stage::Compute},
	};
	Pipeline::Impl::Impl(Application::Impl* app, const json& config)
	{
		m_app = app;
		SetName(config["name"]);
		if (config.contains("tags"))
			for (const auto& t : config["tags"]) AddTag(t);
		json stageFiles = config["files"];
		for (json::iterator t = stageFiles.begin(); t != stageFiles.end(); ++t)
			m_sources[m_stageNames[t.key()]] = ReadPath(t.value());
	}
	void Pipeline::Impl::Load()
	{
		m_shaderModules.clear();
		for (const auto& source : m_sources) {
			DLog("Creating stage %s", source.second.filename().string().data());
			Stage type = source.first;
			auto code = ReadFile(source.second);
			VkShaderModuleCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.codeSize = code.size();
			createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
			VkShaderModule shaderModule;
			ThrowVk(vkCreateShaderModule(m_app->GetVkDevice(), &createInfo, nullptr, &shaderModule));
			m_shaderModules[type] = shaderModule;
		}
		std::vector<VkPipelineShaderStageCreateInfo> stages;
		stages.resize(m_shaderModules.size());
		for (auto& sm : m_shaderModules) {
			VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
			vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			vertShaderStageInfo.stage = (VkShaderStageFlagBits)sm.first;
			vertShaderStageInfo.module = sm.second;
			vertShaderStageInfo.pName = "main";
		}

		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 0;
		vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
		vertexInputInfo.vertexAttributeDescriptionCount = 0;
		vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

		VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)m_app->GetSwapChainExtent().width;
		viewport.height = (float)m_app->GetSwapChainExtent().height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = m_app->GetSwapChainExtent();

		VkPipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		VkPipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;

		VkPipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;

		VkPipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;

		VkDynamicState dynamicStates[] = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_LINE_WIDTH
		};

		VkPipelineDynamicStateCreateInfo dynamicState{};
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.dynamicStateCount = 2;
		dynamicState.pDynamicStates = dynamicStates;

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		ThrowVk(vkCreatePipelineLayout(m_app->GetVkDevice(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout));
	}
	void Pipeline::Impl::Unload()
	{
		for (auto& sm : m_shaderModules) vkDestroyShaderModule(m_app->GetVkDevice(), sm.second, nullptr);
		m_shaderModules.clear();
		vkDestroyPipelineLayout(m_app->GetVkDevice(), m_pipelineLayout, nullptr);
	}
	Resource* Pipeline::Impl::Create(Application::Impl* app, const json& config)
	{
		return new Pipeline::Impl(app, config);
	}
}