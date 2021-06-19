#pragma once
#include <string>
#include <set>
namespace natural {
	struct AttachmentLoadOp {
	private:
		static std::set<std::pair<AttachmentLoadOp, std::string>> m_enumStrings;
		int m_value;
	public:
		AttachmentLoadOp() : m_value(0) {}
		AttachmentLoadOp(int value) : m_value(value) {}
		operator int& () { return m_value; }
		operator int() const { return m_value; }
		std::string ToString();
		static AttachmentLoadOp Parse(const std::string& string);
		static AttachmentLoadOp Load;
		static AttachmentLoadOp Clear;
		static AttachmentLoadOp DontCare;
	};
	struct AttachmentStoreOp {
	private:
		static std::set<std::pair<AttachmentStoreOp, std::string>> m_enumStrings;
		int m_value;
	public:
		AttachmentStoreOp() : m_value(0) {}
		AttachmentStoreOp(int value) : m_value(value) {}
		operator int& () { return m_value; }
		operator int() const { return m_value; }
		std::string ToString();
		static AttachmentStoreOp Parse(const std::string& string);
		static AttachmentStoreOp Store;
		static AttachmentStoreOp DontCare;
	};
}