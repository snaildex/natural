#include "file.h"
#include "logging.h"
#include <fstream>
std::list<std::filesystem::path> ScanFiles(const std::string& extension) {
	std::list<std::filesystem::path> files;
	for (const auto& p : std::filesystem::recursive_directory_iterator(
		std::filesystem::current_path())) {
		const std::string& ext = p.path().extension().string();
		if (ext == extension)
			files.push_back(p.path());
	}
	return files;
}
std::filesystem::path ReadPath(const std::string& path) {
	std::filesystem::path res(path);
	if (!res.is_absolute()) res = std::filesystem::absolute(res);
	return res;
}
std::vector<char> ReadFile(const std::filesystem::path& path) {
	std::ifstream file(path, std::ios::ate | std::ios::binary);
	if (!file.is_open()) {
		DLog("Failed to open file %s", path.string().data());
	}
	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();
	return buffer;
}