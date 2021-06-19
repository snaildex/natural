#pragma once
#include "../common.h"
namespace fs = std::filesystem;
namespace natural {

#define Entity(Type)\
Type ( const Type & ) = delete;\
const Type & operator=( const Type & ) = delete;

#define EnumFlags(Type)\
 constexpr Type operator| ( Type l, Type r) noexcept { return static_cast< Type >(static_cast<std::underlying_type_t< Type >>(l)|static_cast<std::underlying_type_t< Type >>(r));}\
 constexpr Type operator& ( Type l, Type r) noexcept { return static_cast< Type >(static_cast<std::underlying_type_t< Type >>(l)&static_cast<std::underlying_type_t< Type >>(r));}

	template<typename HandleType>
	class HandleBase {
		Entity(HandleBase)

	protected:
		HandleType m_handle;

		HandleBase() { m_handle = {}; };

	public:
		HandleType GetHandle() const noexcept { return m_handle; }
	};

	std::list<fs::path> ScanFiles(const std::string& extension);
	fs::path ReadPath(const std::string& path);
	std::vector<char> ReadFile(const fs::path& path);

	constexpr const char* ___StripFileName(const char* file)
	{
		int i = 0;
		while (file[i] != '\0') i++;
		while (file[i] != '/' && file[i] != '\\') i--;
		return &file[i + 1];
	}

	void ___LogIndent();
	void ___LogUnindent();
	void ___Log(const char* fmt, ...);
	void ___DLog(const char* file, int line, const char* fmt, ...);
#define Log(fmt, ...) natural::___Log(fmt, __VA_ARGS__)
#define DLog(fmt, ...) natural::___DLog(natural::___StripFileName(__FILE__), __LINE__, fmt, __VA_ARGS__)
	void LogSpace();

	class ___LogIndenter {
	public:
		___LogIndenter() { ___LogIndent(); }
		~___LogIndenter() { ___LogUnindent(); }
	};
#define LogIndent() natural::___LogIndenter ___logIndent

	constexpr void ___StripArgName(const char* input, std::string_view& name, const char*& leftover)
	{
		int i = 0;
		while (input[i] != ',' && input[i] != '\0' && input[i] != ' ' && input[i] != '\0') i++;
		name = std::string_view(input, i);
		while (input[i] == ' ' || input[i] == ',') i++;
		leftover = &input[i];
	}

	template <typename T>
	void ___DumpRecursive(std::stringstream& str, const char* argsNames, T first) {
		const char* leftover;
		std::string_view name;
		___StripArgName(argsNames, name, leftover);
		str << name << '=' << first;
	}

	template <typename T, typename ...Args>
	void ___DumpRecursive(std::stringstream& str, const char* argsNames, T first, Args... args) {
		const char* leftover;
		std::string_view name;
		___StripArgName(argsNames, name, leftover);
		str << name << '=' << first << ", ";
		___DumpRecursive(str, leftover, args...);
	}

	template <typename ...Args>
	void ___Dump(const char* file, int line, const char* argsNames, Args... args) {
		std::stringstream str;
		___DumpRecursive(str, argsNames, args...);
		___Log(file, line, str.str().data());
	}

#define Dump(...) ___Dump(natural::___StripFileName(__FILE__), __LINE__, #__VA_ARGS__, __VA_ARGS__)

	bool CheckTail(const std::string& str, const std::string& tail);
	std::string StripTail(const std::string& str, size_t tailLength);
	int StripTailNum(const std::string& str);
	int StripTailNum(const std::string& str, std::string& leftover);

	template<typename T>
	bool ___CheckPtr(const char* file, int line, const T* ptr, const char* ptrName) {
		if (ptr == nullptr) {
			___DLog(file, line, "Object \"%s\" of type \"%s\" is not created", ptrName, typeid(T).name());
			return false;
		}
		return true;
	}

	template<typename T>
	bool ___CheckPtr(const char* file, int line, const std::unique_ptr<T>& ptr, const char* ptrName) {
		if (ptr.get() == nullptr) {
			___DLog(file, line, "Object \"%s\" of type \"%s\" is not created", ptrName, typeid(T).name());
			return false;
		}
		return true;
	}

#define CheckPtr(ptr) natural::___CheckPtr(natural::___StripFileName(__FILE__), __LINE__, ptr, #ptr)
}
