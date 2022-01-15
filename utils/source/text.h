#pragma once
#include <string>
bool CheckTail(const std::string& str, const std::string& tail);
std::string StripTail(const std::string& str, size_t tailLength);
int StripTailNum(const std::string& str);
int StripTailNum(const std::string& str, std::string& leftover);
std::string Replace(std::string subject, const std::string& search, const std::string& replace);
std::string Wrap(const std::string& text, size_t width, size_t indent = 0);
