#include "vulkanHelpers.h"
namespace natural {
	bool ___CheckVk(const char* file, int line, VkResult code, const char* operation) {
		if (code != VK_SUCCESS) {
			___DLog(file, line, "[vulkan] operation \"%s\" failed with code %d", operation, code);
			return false;
		}
		return true;
	}

	VkResult ___ThrowVk(const char* file, int line, VkResult code, const char* operation)
	{
		if (code != VK_SUCCESS && code != VK_TIMEOUT && code != VK_NOT_READY)
			throw VulkanFailedOperationException(file, line, code, operation);
		return code;
	}

	VulkanFailedOperationException::VulkanFailedOperationException(const char* file, int line, VkResult code, const char* operation)
	{
		m_file = file;
		m_line = line;
		m_code = code;
		m_operation = operation;
		sprintf(m_msg.data(), "[%s:%03d] vulkan operation \"%s\" failed with code %d", file, line, operation, code);
	}
}