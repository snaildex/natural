#include <vulkan/vulkan.h>
#include <set>
#include <algorithm>
#include "pipelineBindPoint.h"

namespace natural {
	PipelineBindPoint PipelineBindPoint::Graphics = VK_PIPELINE_BIND_POINT_GRAPHICS;
	PipelineBindPoint PipelineBindPoint::Compute = VK_PIPELINE_BIND_POINT_COMPUTE;
	PipelineBindPoint PipelineBindPoint::RayTracingKhr = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;
	PipelineBindPoint PipelineBindPoint::RayTracingNv = VK_PIPELINE_BIND_POINT_RAY_TRACING_NV;
#define ENUM_STRING_CASE(value) {PipelineBindPoint::value, #value},
	std::set<std::pair<PipelineBindPoint, std::string>> PipelineBindPoint::m_enumStrings = {
		ENUM_STRING_CASE(Graphics)
		ENUM_STRING_CASE(Compute)
		ENUM_STRING_CASE(RayTracingKhr)
		ENUM_STRING_CASE(RayTracingNv)
	};
	std::string PipelineBindPoint::ToString() {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[this](const std::pair<PipelineBindPoint, std::string>& es) { return es.first == m_value; })->second;
	}
	PipelineBindPoint PipelineBindPoint::Parse(const std::string& string) {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[string](const std::pair<PipelineBindPoint, std::string>& es) { return es.second == string; })->first;
	}
}