#pragma once
#include <string>
#include <set>

namespace natural {
	struct PipelineStage {
	private:
		static std::set<std::pair<PipelineStage, std::string>> m_enumStrings;
		int m_value;
	public:
		PipelineStage() : m_value(0) {}
		PipelineStage(int value) : m_value(value) {}
		operator int& () { return m_value; }
		operator int() const { return m_value; }
		PipelineStage operator|(const PipelineStage& rhs) { return PipelineStage(m_value | rhs.m_value); }
		PipelineStage operator&(const PipelineStage& rhs) { return PipelineStage(m_value & rhs.m_value); }
		std::string ToString();
		static PipelineStage Parse(const std::string& string);
		static PipelineStage TopOfPipe;
		static PipelineStage DrawIndirect;
		static PipelineStage VertexInput;
		static PipelineStage VertexShader;
		static PipelineStage TessellationControlShader;
		static PipelineStage TessellationEvaluationShader;
		static PipelineStage GeometryShader;
		static PipelineStage FragmentShader;
		static PipelineStage EarlyFragmentTests;
		static PipelineStage LateFragmentTests;
		static PipelineStage ColorAttachmentOutput;
		static PipelineStage ComputeShader;
		static PipelineStage Transfer;
		static PipelineStage BottomOfPipe;
		static PipelineStage Host;
		static PipelineStage AllGraphics;
		static PipelineStage AllCommands;
		static PipelineStage TransformFeedbackExt;
		static PipelineStage ConditionalRenderingExt;
		static PipelineStage AccelerationStructureBuildKhr;
		static PipelineStage RayTracingShaderKhr;
		static PipelineStage ShadingRateImageNv;
		static PipelineStage TaskShaderNv;
		static PipelineStage MeshShaderNv;
		static PipelineStage FragmentDensityProcessExt;
		static PipelineStage CommandPreprocessNv;
		static PipelineStage NoneKhr;
		static PipelineStage RayTracingShaderNv;
		static PipelineStage AccelerationStructureBuildNv;
		static PipelineStage FragmentShadingRateAttachmentKhr;
	};
}