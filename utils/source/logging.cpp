#include "logging.h"
#include <vector>
#include <filesystem>
#include <list>
#include <mutex>
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include "clock.h"

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

std::mutex LogLock;
Clock::TimePoint LogStart = Clock::Now();

int LogIndentLevel;
void ___LogIndent() { std::lock_guard<std::mutex> g(LogLock); LogIndentLevel++; }
void ___LogUnindent() { std::lock_guard<std::mutex> g(LogLock); LogIndentLevel--; }

std::ofstream LogFile("Log.txt");
thread_local char LogBuf[4096];
void ___Log(const char* fmt, ...)
{
	std::lock_guard<std::mutex> g(LogLock);
	for (int i = 0; i < LogIndentLevel; ++i) LogFile << "    ";
	va_list vargs;
	va_start(vargs, fmt);
	vsprintf(LogBuf, fmt, vargs);
	va_end(vargs);
	LogFile << LogBuf << std::endl;
	std::cout << LogBuf << std::endl;
}

void ___DLog(const char* file, int line, const char* fmt, ...)
{
	std::lock_guard<std::mutex> g(LogLock);
	if (file != nullptr) {
		char buf[64];
		if (line >= 0)
			sprintf(buf, "%s:%03d", file, line);
		else
			sprintf(buf, "%s", file);
		if (fmt[0] == '[')
			sprintf(LogBuf, "[%s][%p][%s]", Clock::PrintDuration(Clock::Duration(LogStart, Clock::Now())).c_str(), std::this_thread::get_id(), buf);
		else
			sprintf(LogBuf, "[%s][%p][%s] ", Clock::PrintDuration(Clock::Duration(LogStart, Clock::Now())).c_str(), std::this_thread::get_id(), buf);
		LogFile << LogBuf;
	}
	if (line >= 0) for (int i = 0; i < LogIndentLevel; ++i) LogFile << "    ";
	va_list vargs;
	va_start(vargs, fmt);
	vsprintf(LogBuf, fmt, vargs);
	va_end(vargs);
	LogFile << LogBuf << std::endl;
	std::cout << LogBuf << std::endl;
}

void LogSpace()
{
	std::lock_guard<std::mutex> g(LogLock);
	LogFile << std::endl;
}