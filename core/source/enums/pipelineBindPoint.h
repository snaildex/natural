#pragma once
#include <string>
#include <set>
namespace natural {
	struct PipelineBindPoint {
	private:
		static std::set<std::pair<PipelineBindPoint, std::string>> m_enumStrings;
		int m_value;
	public:
		PipelineBindPoint() : m_value(0) {}
		PipelineBindPoint(int value) : m_value(value) {}
		operator int& () { return m_value; }
		operator int() const { return m_value; }
		std::string ToString();
		static PipelineBindPoint Parse(const std::string& string);
		static PipelineBindPoint Graphics;
		static PipelineBindPoint Compute;
		static PipelineBindPoint RayTracingKhr;
		static PipelineBindPoint RayTracingNv;
	};
}