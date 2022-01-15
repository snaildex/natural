#pragma once
#include <string_view>
#include <sstream>

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
#define Log(fmt, ...) ___Log(fmt, __VA_ARGS__)
#define DLog(fmt, ...) ___DLog(___StripFileName(__FILE__), __LINE__, fmt, __VA_ARGS__)
void LogSpace();

class ___LogIndenter {
public:
	___LogIndenter() { ___LogIndent(); }
	~___LogIndenter() { ___LogUnindent(); }
};
#define LogIndent() ___LogIndenter ___logIndent

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

#define Dump(...) ___Dump(___StripFileName(__FILE__), __LINE__, #__VA_ARGS__, __VA_ARGS__)

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

#define CheckPtr(ptr) ___CheckPtr(___StripFileName(__FILE__), __LINE__, ptr, #ptr)
