#include <vulkan/vulkan.h>
#include <set>
#include <algorithm>
#include "imageLayout.h"

namespace natural {
	ImageLayout ImageLayout::Undefined = VK_IMAGE_LAYOUT_UNDEFINED;
	ImageLayout ImageLayout::General = VK_IMAGE_LAYOUT_GENERAL;
	ImageLayout ImageLayout::ColorAttachmentOptimal = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	ImageLayout ImageLayout::DepthStencilAttachmentOptimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	ImageLayout ImageLayout::DepthStencilReadOnlyOptimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
	ImageLayout ImageLayout::ShaderReadOnlyOptimal = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	ImageLayout ImageLayout::TransferSrcOptimal = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
	ImageLayout ImageLayout::TransferDstOptimal = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	ImageLayout ImageLayout::Preintialized = VK_IMAGE_LAYOUT_PREINITIALIZED;
	ImageLayout ImageLayout::DepthReadOnlyStencilAttachmentOptimal = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL;
	ImageLayout ImageLayout::DepthAttachmentStencilReadOnlyOptimal = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL;
	ImageLayout ImageLayout::DepthAttachmentOptimal = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
	ImageLayout ImageLayout::DepthReadOnlyOptimal = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL;
	ImageLayout ImageLayout::StencilAttachmentOptimal = VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL;
	ImageLayout ImageLayout::StencilReadOnlyOptimal = VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL;
	ImageLayout ImageLayout::PresentSrcKhr = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	ImageLayout ImageLayout::SharedPresentKhr = VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR;
	ImageLayout ImageLayout::ShadingRateOptimalNv = VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV;
	ImageLayout ImageLayout::FragmentDensityMapOptimalExt = VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT;
	ImageLayout ImageLayout::DepthReadOnlyStencilAttachmentOptimalKhr = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR;
	ImageLayout ImageLayout::DepthAttachmentStencilReadOnlyOptimalKhr = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR;
	ImageLayout ImageLayout::DepthAttachmentOptimalKhr = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL_KHR;
	ImageLayout ImageLayout::DepthReadOnlyOptimalKhr = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL_KHR;
	ImageLayout ImageLayout::StencilAttachmentOptimalKhr = VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL_KHR;
	ImageLayout ImageLayout::StencilReadOnlyOptimalKhr = VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL_KHR;
#define ENUM_STRING_CASE(value) {ImageLayout::value, #value},
	std::set<std::pair<ImageLayout, std::string>> ImageLayout::m_enumStrings = {
		ENUM_STRING_CASE(Undefined)
		ENUM_STRING_CASE(General)
		ENUM_STRING_CASE(ColorAttachmentOptimal)
		ENUM_STRING_CASE(DepthStencilAttachmentOptimal)
		ENUM_STRING_CASE(DepthStencilReadOnlyOptimal)
		ENUM_STRING_CASE(ShaderReadOnlyOptimal)
		ENUM_STRING_CASE(TransferSrcOptimal)
		ENUM_STRING_CASE(TransferDstOptimal)
		ENUM_STRING_CASE(Preintialized)
		ENUM_STRING_CASE(DepthReadOnlyStencilAttachmentOptimal)
		ENUM_STRING_CASE(DepthAttachmentStencilReadOnlyOptimal)
		ENUM_STRING_CASE(DepthAttachmentOptimal)
		ENUM_STRING_CASE(DepthReadOnlyOptimal)
		ENUM_STRING_CASE(StencilAttachmentOptimal)
		ENUM_STRING_CASE(StencilReadOnlyOptimal)
		ENUM_STRING_CASE(PresentSrcKhr)
		ENUM_STRING_CASE(SharedPresentKhr)
		ENUM_STRING_CASE(ShadingRateOptimalNv)
		ENUM_STRING_CASE(FragmentDensityMapOptimalExt)
		ENUM_STRING_CASE(DepthReadOnlyStencilAttachmentOptimalKhr)
		ENUM_STRING_CASE(DepthAttachmentStencilReadOnlyOptimalKhr)
		ENUM_STRING_CASE(DepthAttachmentOptimalKhr)
		ENUM_STRING_CASE(DepthReadOnlyOptimalKhr)
		ENUM_STRING_CASE(StencilAttachmentOptimalKhr)
		ENUM_STRING_CASE(StencilReadOnlyOptimalKhr)
	};
	std::string ImageLayout::ToString() {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[this](const std::pair<ImageLayout, std::string>& es) { return es.first == m_value; })->second;
	}
	ImageLayout ImageLayout::Parse(const std::string& string) {
		return std::find_if(m_enumStrings.cbegin(), m_enumStrings.cend(),
			[string](const std::pair<ImageLayout, std::string>& es) { return es.second == string; })->first;
	}
}