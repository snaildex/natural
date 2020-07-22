#pragma once
#include "helpers.h"
#include "../common.h"
#include <vulkan/vulkan.h>
namespace natural {

	class VulkanFailedOperationException : public std::exception {
		const char* m_file;
		int m_line;
		VkResult m_code;
		const char* m_operation;
		std::array<char, 512> m_msg;
	public:
		char const* what() const { return m_msg.data(); };
		VulkanFailedOperationException(const char* file, int line, VkResult code, const char* operation);
	};

	bool ___CheckVk(const char* file, int line, VkResult code, const char* operation);
	void ___ThrowVk(const char* file, int line, VkResult code, const char* operation);

#define CheckVk(operation) natural::___CheckVk(natural::___StripFileName(__FILE__), __LINE__, operation, #operation)
#define ThrowVk(operation) natural::___ThrowVk(natural::___StripFileName(__FILE__), __LINE__, operation, #operation)
}