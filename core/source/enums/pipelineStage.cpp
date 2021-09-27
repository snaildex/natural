#include <vulkan/vulkan.h>
#include <set>
#include <algorithm>
#include "pipelineStage.h"

namespace natural {
	PipelineStage PipelineStage::TopOfPipe = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
	PipelineStage PipelineStage::DrawIndirect = VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT;
	PipelineStage PipelineStage::VertexInput = VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
	PipelineStage PipelineStage::VertexShader = VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;
	PipelineStage PipelineStage::TessellationControlShader = VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT;
	PipelineStage PipelineStage::TessellationEvaluationShader = VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT;
	PipelineStage PipelineStage::GeometryShader = VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT;
	PipelineStage PipelineStage::FragmentShader = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	PipelineStage PipelineStage::EarlyFragmentTests = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	PipelineStage PipelineStage::LateFragmentTests = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
	PipelineStage PipelineStage::ColorAttachmentOutput = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	PipelineStage PipelineStage::ComputeShader = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
	PipelineStage PipelineStage::Transfer = VK_PIPELINE_STAGE_TRANSFER_BIT;
	PipelineStage PipelineStage::BottomOfPipe = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
	PipelineStage PipelineStage::Host = VK_PIPELINE_STAGE_HOST_BIT;
	PipelineStage PipelineStage::AllGraphics = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;
	PipelineStage PipelineStage::AllCommands = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
	PipelineStage PipelineStage::TransformFeedbackExt = VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT;
	PipelineStage PipelineStage::ConditionalRenderingExt = VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT;
	PipelineStage PipelineStage::AccelerationStructureBuildKhr = VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR;
	PipelineStage PipelineStage::RayTracingShaderKhr = VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR;
	PipelineStage PipelineStage::ShadingRateImageNv = VK_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV;
	PipelineStage PipelineStage::TaskShaderNv = VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV;
	PipelineStage PipelineStage::MeshShaderNv = VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV;
	PipelineStage PipelineStage::FragmentDensityProcessExt = VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT;
	PipelineStage PipelineStage::CommandPreprocessNv = VK_PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_NV;
	PipelineStage PipelineStage::NoneKhr = VK_PIPELINE_STAGE_NONE_KHR;
	PipelineStage PipelineStage::RayTracingShaderNv = VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_NV;
	PipelineStage PipelineStage::AccelerationStructureBuildNv = VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV;
	PipelineStage PipelineStage::FragmentShadingRateAttachmentKhr = VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR;
#define ENUM_STRING_CASE(value) {PipelineStage::value, #value},
	std::set<std::pair<PipelineStage, std::string>> PipelineStage::m_enumStrings = {
		ENUM_STRING_CASE(TopOfPipe)
		ENUM_STRING_CASE(DrawIndirect)
		ENUM_STRING_CASE(VertexInput)
		ENUM_STRING_CASE(VertexShader)
		ENUM_STRING_CASE(TessellationControlShader)
		ENUM_STRING_CASE(TessellationEvaluationShader)
		ENUM_STRING_CASE(GeometryShader)
		ENUM_STRING_CASE(FragmentShader)
		ENUM_STRING_CASE(EarlyFragmentTests)
		ENUM_STRING_CASE(LateFragmentTests)
		ENUM_STRING_CASE(ColorAttachmentOutput)
		ENUM_STRING_CASE(ComputeShader)
		ENUM_STRING_CASE(Transfer)
		ENUM_STRING_CASE(BottomOfPipe)
		ENUM_STRING_CASE(Host)
		ENUM_STRING_CASE(AllGraphics)
		ENUM_STRING_CASE(AllCommands)
		ENUM_STRING_CASE(TransformFeedbackExt)
		ENUM_STRING_CASE(ConditionalRenderingExt)
		ENUM_STRING_CASE(AccelerationStructureBuildKhr)
		ENUM_STRING_CASE(RayTracingShaderKhr)
		ENUM_STRING_CASE(ShadingRateImageNv)
		ENUM_STRING_CASE(TaskShaderNv)
		ENUM_STRING_CASE(MeshShaderNv)
		ENUM_STRING_CASE(FragmentDensityProcessExt)
		ENUM_STRING_CASE(CommandPreprocessNv)
		ENUM_STRING_CASE(NoneKhr)
		ENUM_STRING_CASE(RayTracingShaderNv)
		ENUM_STRING_CASE(AccelerationStructureBuildNv)
		ENUM_STRING_CASE(FragmentShadingRateAttachmentKhr)
	};
	std::string PipelineStage::ToString() {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[this](const std::pair<PipelineStage, std::string>& es) { return es.first == m_value; })->second;
	}
	PipelineStage PipelineStage::Parse(const std::string& string) {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[string](const std::pair<PipelineStage, std::string>& es) { return es.second == string; })->first;
	}
}