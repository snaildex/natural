#include "shaderImpl.h"
namespace natural {
	std::map<std::string, Shader::Impl::Stage> Shader::Impl::m_stageNames{
		{"vert",Shader::Impl::Stage::Vertex},
		{"tesc",Shader::Impl::Stage::TessCtrl},
		{"tese",Shader::Impl::Stage::TessEval},
		{"geom",Shader::Impl::Stage::Geometry},
		{"frag",Shader::Impl::Stage::Fragment},
		{"comp",Shader::Impl::Stage::Compute},
	};
	Shader::Impl::Impl(Application::Impl* app, const json& config)
	{
		m_app = app;
		SetName(config["name"]);
		if (config.contains("tags"))
			for (const auto& t : config["tags"]) AddTag(t);
		json stageFiles = config["files"];
		for (json::iterator t = stageFiles.begin(); t != stageFiles.end(); ++t)
			m_sources[m_stageNames[t.key()]] = ReadPath(t.value());
	}
	void Shader::Impl::Load()
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
	}
	void Shader::Impl::Unload()
	{
		for (auto& sm : m_shaderModules) vkDestroyShaderModule(m_app->GetVkDevice(), sm.second, nullptr);
		m_shaderModules.clear();
	}
	Resource* Shader::Impl::Create(Application::Impl* app, const json& config)
	{
		return new Shader::Impl(app, config);
	}
}