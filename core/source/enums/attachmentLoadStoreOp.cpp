#include <vulkan/vulkan.h>
#include <set>
#include <algorithm>
#include "attachmentLoadStoreOp.h"

namespace natural {
	AttachmentLoadOp AttachmentLoadOp::Load = VK_ATTACHMENT_LOAD_OP_LOAD;
	AttachmentLoadOp AttachmentLoadOp::Clear = VK_ATTACHMENT_LOAD_OP_CLEAR;
	AttachmentLoadOp AttachmentLoadOp::DontCare = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
#define ENUM_STRING_CASE(value) {AttachmentLoadOp::value, #value},
	std::set<std::pair<AttachmentLoadOp, std::string>> AttachmentLoadOp::m_enumStrings = {
		ENUM_STRING_CASE(Load)
		ENUM_STRING_CASE(Clear)
		ENUM_STRING_CASE(DontCare)
	};
	std::string AttachmentLoadOp::ToString() {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[this](const std::pair<AttachmentLoadOp, std::string>& es) { return es.first == m_value; })->second;
	}
	AttachmentLoadOp AttachmentLoadOp::Parse(const std::string& string) {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[string](const std::pair<AttachmentLoadOp, std::string>& es) { return es.second == string; })->first;
	}
	AttachmentStoreOp AttachmentStoreOp::Store = VK_ATTACHMENT_STORE_OP_STORE;
	AttachmentStoreOp AttachmentStoreOp::DontCare = VK_ATTACHMENT_STORE_OP_DONT_CARE;
#define ENUM_STRING_CASE(value) {AttachmentStoreOp::value, #value},
	std::set<std::pair<AttachmentStoreOp, std::string>> AttachmentStoreOp::m_enumStrings = {
		ENUM_STRING_CASE(Store)
		ENUM_STRING_CASE(DontCare)
	};
	std::string AttachmentStoreOp::ToString() {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[this](const std::pair<AttachmentStoreOp, std::string>& es) { return es.first == m_value; })->second;
	}
	AttachmentStoreOp AttachmentStoreOp::Parse(const std::string& string) {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[string](const std::pair<AttachmentStoreOp, std::string>& es) { return es.second == string; })->first;
	}
}