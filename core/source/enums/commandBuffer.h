#pragma once
#include <string>
#include <set>
namespace natural {
	struct CommandBufferUsage {
	private:
		static std::set<std::pair<CommandBufferUsage, std::string>> m_enumStrings;
		int m_value;
	public:
		CommandBufferUsage() : m_value(0) {}
		CommandBufferUsage(int value) : m_value(value) {}
		operator int& () { return m_value; }
		operator int() const { return m_value; }
		CommandBufferUsage operator|(const CommandBufferUsage& rhs) { return CommandBufferUsage(m_value | rhs.m_value); }
		CommandBufferUsage operator&(const CommandBufferUsage& rhs) { return CommandBufferUsage(m_value & rhs.m_value); }
		std::string ToString();
		static CommandBufferUsage Parse(const std::string& string);
		static CommandBufferUsage OneTimeSubmit;
		static CommandBufferUsage RenderPassContinue;
		static CommandBufferUsage SimultaneousUse;
	};
	struct SubpassContents {
	private:
		static std::set<std::pair<SubpassContents, std::string>> m_enumStrings;
		int m_value;
	public:
		SubpassContents() : m_value(0) {}
		SubpassContents(int value) : m_value(value) {}
		operator int& () { return m_value; }
		operator int() const { return m_value; }
		std::string ToString();
		static SubpassContents Parse(const std::string& string);
		static SubpassContents Inline;
		static SubpassContents SecondaryCommandBuffers;
	};
}