#include <vulkan/vulkan.h>
#include <set>
#include <algorithm>
#include "commandBuffer.h"

namespace natural {
	CommandBufferUsage CommandBufferUsage::OneTimeSubmit = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	CommandBufferUsage CommandBufferUsage::RenderPassContinue = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
	CommandBufferUsage CommandBufferUsage::SimultaneousUse = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
#define ENUM_STRING_CASE(value) {CommandBufferUsage::value, #value},
	std::set<std::pair<CommandBufferUsage, std::string>> CommandBufferUsage::m_enumStrings = {
		ENUM_STRING_CASE(OneTimeSubmit)
		ENUM_STRING_CASE(RenderPassContinue)
		ENUM_STRING_CASE(SimultaneousUse)
	};
	std::string CommandBufferUsage::ToString() {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[this](const std::pair<CommandBufferUsage, std::string>& es) { return es.first == m_value; })->second;
	}
	CommandBufferUsage CommandBufferUsage::Parse(const std::string& string) {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[string](const std::pair<CommandBufferUsage, std::string>& es) { return es.second == string; })->first;
	}

	SubpassContents SubpassContents::Inline = VK_SUBPASS_CONTENTS_INLINE;
	SubpassContents SubpassContents::SecondaryCommandBuffers = VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS;
#define ENUM_STRING_CASE(value) {SubpassContents::value, #value},
	std::set<std::pair<SubpassContents, std::string>> SubpassContents::m_enumStrings = {
		ENUM_STRING_CASE(Inline)
		ENUM_STRING_CASE(SecondaryCommandBuffers)
	};
	std::string SubpassContents::ToString() {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[this](const std::pair<SubpassContents, std::string>& es) { return es.first == m_value; })->second;
	}
	SubpassContents SubpassContents::Parse(const std::string& string) {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[string](const std::pair<SubpassContents, std::string>& es) { return es.second == string; })->first;
	}
}