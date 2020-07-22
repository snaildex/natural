#pragma once
#include "pipeline.h"
#include "../../application/applicationImpl.h"
#include "../resourceBuilderMap.h"
#include <vulkan/vulkan.h>
#include "../../helpers/vulkanHelpers.h"
namespace natural {
	class Pipeline::Impl : public Pipeline {
		enum class Stage {
			Vertex = VK_SHADER_STAGE_VERTEX_BIT,
			TessCtrl = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
			TessEval = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
			Geometry = VK_SHADER_STAGE_GEOMETRY_BIT,
			Fragment = VK_SHADER_STAGE_FRAGMENT_BIT,
			Compute = VK_SHADER_STAGE_COMPUTE_BIT
		};
		Application::Impl* m_app;
		static std::map<std::string, Stage> m_stageNames;
		std::map<Stage, fs::path> m_sources;
		std::map<Stage, VkShaderModule> m_shaderModules;
		VkPipelineLayout m_pipelineLayout;

	protected:
		void Load();
		void Unload();
	public:
		Impl(Application::Impl* app, const json& config);
		static Resource* Create(Application::Impl* app, const json& config);
	};
}