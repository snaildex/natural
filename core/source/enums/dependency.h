#pragma once
#include <string>
#include <set>

namespace natural {
	struct Dependency {
	private:
		static std::set<std::pair<Dependency, std::string>> m_enumStrings;
		int m_value;
	public:
		Dependency() : m_value(0) {}
		Dependency(int value) : m_value(value) {}
		operator int& () { return m_value; }
		operator int() const { return m_value; }
		Dependency operator|(const Dependency& rhs) { return Dependency(m_value | rhs.m_value); }
		Dependency operator&(const Dependency& rhs) { return Dependency(m_value & rhs.m_value); }
		std::string ToString();
		static Dependency Parse(const std::string& string);
		static Dependency ByRegionBit;
		static Dependency DeviceGroupBit;
		static Dependency ViewLocalBit;
		static Dependency ViewLocalBitKhr;
		static Dependency DeviceGroupBitKhr;
	};
}