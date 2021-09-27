#include <vulkan/vulkan.h>
#include <set>
#include <algorithm>
#include "dependency.h"

namespace natural {
	Dependency Dependency::ByRegionBit = VK_DEPENDENCY_BY_REGION_BIT;
	Dependency Dependency::DeviceGroupBit = VK_DEPENDENCY_DEVICE_GROUP_BIT;
	Dependency Dependency::ViewLocalBit = VK_DEPENDENCY_VIEW_LOCAL_BIT;
	Dependency Dependency::ViewLocalBitKhr = VK_DEPENDENCY_VIEW_LOCAL_BIT_KHR;
	Dependency Dependency::DeviceGroupBitKhr = VK_DEPENDENCY_DEVICE_GROUP_BIT_KHR;
#define ENUM_STRING_CASE(value) {Dependency::value, #value},
	std::set<std::pair<Dependency, std::string>> Dependency::m_enumStrings = {
		ENUM_STRING_CASE(ByRegionBit)
		ENUM_STRING_CASE(DeviceGroupBit)
		ENUM_STRING_CASE(ViewLocalBit)
		ENUM_STRING_CASE(ViewLocalBitKhr)
		ENUM_STRING_CASE(DeviceGroupBitKhr)
	};
	std::string Dependency::ToString() {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[this](const std::pair<Dependency, std::string>& es) { return es.first == m_value; })->second;
	}
	Dependency Dependency::Parse(const std::string& string) {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[string](const std::pair<Dependency, std::string>& es) { return es.second == string; })->first;
	}
}