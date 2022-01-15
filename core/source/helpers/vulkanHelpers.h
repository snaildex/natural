#pragma once
#include <utils.h>
#include "../common.h"
#include <vulkan/vulkan.h>
namespace natural {
	template<typename HandleType>
	class HandleBase {
		Entity(HandleBase)

	protected:
		HandleType m_handle;

		HandleBase() { m_handle = {}; };

	public:
		HandleType GetHandle() const noexcept { return m_handle; }
	};

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
	VkResult ___ThrowVk(const char* file, int line, VkResult code, const char* operation);

#define CheckVk(operation) natural::___CheckVk(___StripFileName(__FILE__), __LINE__, operation, #operation)
#define ThrowVk(operation) natural::___ThrowVk(___StripFileName(__FILE__), __LINE__, operation, #operation)
}