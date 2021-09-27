#include <vulkan/vulkan.h>
#include <set>
#include <algorithm>
#include "access.h"

namespace natural {
	Access Access::IndirectCommandRead = VK_ACCESS_INDIRECT_COMMAND_READ_BIT;
	Access Access::IndexRead = VK_ACCESS_INDEX_READ_BIT;
	Access Access::VertexAttributeRead = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
	Access Access::UniformRead = VK_ACCESS_UNIFORM_READ_BIT;
	Access Access::InputAttachmentRead = VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
	Access Access::ShaderRead = VK_ACCESS_SHADER_READ_BIT;
	Access Access::ShaderWrite = VK_ACCESS_SHADER_WRITE_BIT;
	Access Access::ColorAttachmentRead = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
	Access Access::ColorAttachmentWrite = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	Access Access::DepthStencilAttachmentRead = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
	Access Access::DepthStencilAttachmentWrite = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	Access Access::TransferRead = VK_ACCESS_TRANSFER_READ_BIT;
	Access Access::TransferWrite = VK_ACCESS_TRANSFER_WRITE_BIT;
	Access Access::HostRead = VK_ACCESS_HOST_READ_BIT;
	Access Access::HostWrite = VK_ACCESS_HOST_WRITE_BIT;
	Access Access::MemoryRead = VK_ACCESS_MEMORY_READ_BIT;
	Access Access::MemoryWrite = VK_ACCESS_MEMORY_WRITE_BIT;
	Access Access::TransformFeedbackWriteExt = VK_ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT_EXT;
	Access Access::TransformFeedbackCounterReadExt = VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT;
	Access Access::TransformFeedbackCounterWriteExt = VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT;
	Access Access::ConditionalRenderingReadExt = VK_ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT;
	Access Access::ColorAttachmentReadNoncoherentExt = VK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT;
	Access Access::AccelerationStructureReadKhr = VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR;
	Access Access::AccelerationStructureWriteKhr = VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR;
	Access Access::ShadingRateImageReadNv = VK_ACCESS_SHADING_RATE_IMAGE_READ_BIT_NV;
	Access Access::FragmentDensityMapReadExt = VK_ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT_EXT;
	Access Access::CommandPreprocessReadNv = VK_ACCESS_COMMAND_PREPROCESS_READ_BIT_NV;
	Access Access::CommandPreprocessWriteNv = VK_ACCESS_COMMAND_PREPROCESS_WRITE_BIT_NV;
	Access Access::NoneKhr = VK_ACCESS_NONE_KHR;
	Access Access::AccelerationStructureReadNv = VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_NV;
	Access Access::AccelerationStructureWriteNv = VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_NV;
	Access Access::FragmentShadingRateAttachmentReadKhr = VK_ACCESS_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR;
#define ENUM_STRING_CASE(value) {Access::value, #value},
	std::set<std::pair<Access, std::string>> Access::m_enumStrings = {
		ENUM_STRING_CASE(IndirectCommandRead)
		ENUM_STRING_CASE(IndexRead)
		ENUM_STRING_CASE(VertexAttributeRead)
		ENUM_STRING_CASE(UniformRead)
		ENUM_STRING_CASE(InputAttachmentRead)
		ENUM_STRING_CASE(ShaderRead)
		ENUM_STRING_CASE(ShaderWrite)
		ENUM_STRING_CASE(ColorAttachmentRead)
		ENUM_STRING_CASE(ColorAttachmentWrite)
		ENUM_STRING_CASE(DepthStencilAttachmentRead)
		ENUM_STRING_CASE(DepthStencilAttachmentWrite)
		ENUM_STRING_CASE(TransferRead)
		ENUM_STRING_CASE(TransferWrite)
		ENUM_STRING_CASE(HostRead)
		ENUM_STRING_CASE(HostWrite)
		ENUM_STRING_CASE(MemoryRead)
		ENUM_STRING_CASE(MemoryWrite)
		ENUM_STRING_CASE(TransformFeedbackWriteExt)
		ENUM_STRING_CASE(TransformFeedbackCounterReadExt)
		ENUM_STRING_CASE(TransformFeedbackCounterWriteExt)
		ENUM_STRING_CASE(ConditionalRenderingReadExt)
		ENUM_STRING_CASE(ColorAttachmentReadNoncoherentExt)
		ENUM_STRING_CASE(AccelerationStructureReadKhr)
		ENUM_STRING_CASE(AccelerationStructureWriteKhr)
		ENUM_STRING_CASE(ShadingRateImageReadNv)
		ENUM_STRING_CASE(FragmentDensityMapReadExt)
		ENUM_STRING_CASE(CommandPreprocessReadNv)
		ENUM_STRING_CASE(CommandPreprocessWriteNv)
		ENUM_STRING_CASE(NoneKhr)
		ENUM_STRING_CASE(AccelerationStructureReadNv)
		ENUM_STRING_CASE(AccelerationStructureWriteNv)
		ENUM_STRING_CASE(FragmentShadingRateAttachmentReadKhr)
	};
	std::string Access::ToString() {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[this](const std::pair<Access, std::string>& es) { return es.first == m_value; })->second;
	}
	Access Access::Parse(const std::string& string) {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[string](const std::pair<Access, std::string>& es) { return es.second == string; })->first;
	}
}