#pragma once
#include <filesystem>
#include <list>
#include <vector>
std::list<std::filesystem::path> ScanFiles(const std::string& extension);
std::filesystem::path ReadPath(const std::string& path);
std::vector<char> ReadFile(const std::filesystem::path& path);