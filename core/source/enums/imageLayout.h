#pragma once
#include <string>
#include <set>
namespace natural {
	struct ImageLayout {
	private:
		static std::set<std::pair<ImageLayout, std::string>> m_enumStrings;
		int m_value;
	public:
		ImageLayout() : m_value(0) {}
		ImageLayout(int value) : m_value(value) {}
		operator int& () { return m_value; }
		operator int() const { return m_value; }
		std::string ToString();
		static ImageLayout Parse(const std::string& string);
		static ImageLayout Undefined;
		static ImageLayout General;
		static ImageLayout ColorAttachmentOptimal;
		static ImageLayout DepthStencilAttachmentOptimal;
		static ImageLayout DepthStencilReadOnlyOptimal;
		static ImageLayout ShaderReadOnlyOptimal;
		static ImageLayout TransferSrcOptimal;
		static ImageLayout TransferDstOptimal;
		static ImageLayout Preintialized;
		static ImageLayout DepthReadOnlyStencilAttachmentOptimal;
		static ImageLayout DepthAttachmentStencilReadOnlyOptimal;
		static ImageLayout DepthAttachmentOptimal;
		static ImageLayout DepthReadOnlyOptimal;
		static ImageLayout StencilAttachmentOptimal;
		static ImageLayout StencilReadOnlyOptimal;
		static ImageLayout PresentSrcKhr;
		static ImageLayout SharedPresentKhr;
		static ImageLayout ShadingRateOptimalNv;
		static ImageLayout FragmentDensityMapOptimalExt;
		static ImageLayout DepthReadOnlyStencilAttachmentOptimalKhr;
		static ImageLayout DepthAttachmentStencilReadOnlyOptimalKhr;
		static ImageLayout DepthAttachmentOptimalKhr;
		static ImageLayout DepthReadOnlyOptimalKhr;
		static ImageLayout StencilAttachmentOptimalKhr;
		static ImageLayout StencilReadOnlyOptimalKhr;
	};
}