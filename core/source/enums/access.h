#pragma once
#include <string>
#include <set>

namespace natural {
	struct Access {
	private:
		static std::set<std::pair<Access, std::string>> m_enumStrings;
		int m_value;
	public:
		Access() : m_value(0) {}
		Access(int value) : m_value(value) {}
		operator int& () { return m_value; }
		operator int() const { return m_value; }
		Access operator|(const Access& rhs) { return Access(m_value | rhs.m_value); }
		Access operator&(const Access& rhs) { return Access(m_value & rhs.m_value); }
		std::string ToString();
		static Access Parse(const std::string& string);
		static Access IndirectCommandRead;
		static Access IndexRead;
		static Access VertexAttributeRead;
		static Access UniformRead;
		static Access InputAttachmentRead;
		static Access ShaderRead;
		static Access ShaderWrite;
		static Access ColorAttachmentRead;
		static Access ColorAttachmentWrite;
		static Access DepthStencilAttachmentRead;
		static Access DepthStencilAttachmentWrite;
		static Access TransferRead;
		static Access TransferWrite;
		static Access HostRead;
		static Access HostWrite;
		static Access MemoryRead;
		static Access MemoryWrite;
		static Access TransformFeedbackWriteExt;
		static Access TransformFeedbackCounterReadExt;
		static Access TransformFeedbackCounterWriteExt;
		static Access ConditionalRenderingReadExt;
		static Access ColorAttachmentReadNoncoherentExt;
		static Access AccelerationStructureReadKhr;
		static Access AccelerationStructureWriteKhr;
		static Access ShadingRateImageReadNv;
		static Access FragmentDensityMapReadExt;
		static Access CommandPreprocessReadNv;
		static Access CommandPreprocessWriteNv;
		static Access NoneKhr;
		static Access AccelerationStructureReadNv;
		static Access AccelerationStructureWriteNv;
		static Access FragmentShadingRateAttachmentReadKhr;
	};
}