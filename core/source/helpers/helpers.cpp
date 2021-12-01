#include "helpers.h"

using namespace std;
namespace fs = std::filesystem;
namespace natural {
	list<fs::path> ScanFiles(const string& extension) {
		list<fs::path> files;
		for (const auto& p : fs::recursive_directory_iterator(
			fs::current_path())) {
			const string& ext = p.path().extension().string();
			if (ext == extension)
				files.push_back(p.path());
		}
		return files;
	}

	fs::path ReadPath(const std::string& path) {
		fs::path res(path);
		if (!res.is_absolute()) res = fs::absolute(res);
		return res;
	}

	std::vector<char> ReadFile(const fs::path& path) {
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

	bool CheckTail(const std::string& str, const std::string& tail)
	{
		if (str.length() < tail.length()) return false;
		return strncmp(&str[str.length() - tail.length()], tail.data(), tail.length()) == 0;
	}

	std::string StripTail(const std::string& str, size_t tailLength)
	{
		return str.substr(0, str.length() - tailLength);
	}

	int StripTailNum(const std::string& str)
	{
		size_t i = str.length() - 1;
		if (!isdigit(str[i])) return -1;
		while (isdigit(str[i--]));
		return atoi(&str.data()[i + 1]);
	}

	int StripTailNum(const std::string& str, std::string& leftover)
	{
		size_t i = str.length() - 1;
		if (!isdigit(str[i])) return -1;
		while (isdigit(str[i--]));
		leftover = str.substr(0, i + 2);
		return atoi(&str.data()[i + 1]);
	}

	std::string Replace(std::string subject, const std::string& search, const std::string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return subject;
	}

	std::string Wrap(const std::string& text, size_t width, size_t indent) {
		istringstream isstr(text);
		ostringstream osstr;
		string word;
		size_t clinewidth = 0;
		while (!isstr.eof()) {
			isstr >> word;
			if (word.size() >= width)
				osstr << word << ' ';
			else {
				if (clinewidth + word.size() > width) {
					osstr << '\n';
					for (int i = 0; i < indent; ++i) osstr << ' ';
					clinewidth = indent;
				}
				osstr << word << ' ';
				clinewidth += word.size() + 1;
				if (isstr.peek() == '\n' || isstr.peek() == '\r') {
					osstr << '\n';
					for (int i = 0; i < indent; ++i) osstr << ' ';
					clinewidth = indent;
				}
			}
		}
		return osstr.str();
	}

	mutex LogLock;

	int LogIndentLevel;
	void ___LogIndent() { lock_guard<mutex> g(LogLock); LogIndentLevel++; }
	void ___LogUnindent() { lock_guard<mutex> g(LogLock); LogIndentLevel--; }

	ofstream LogFile("Log.txt");
	thread_local char LogBuf[4096];
	void ___Log(const char* fmt, ...)
	{
		lock_guard<mutex> g(LogLock);
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
		lock_guard<mutex> g(LogLock);
		if (file != nullptr) {
			char buf[64];
			if (line >= 0)
				sprintf(buf, "%s:%03d", file, line);
			else
				sprintf(buf, "%s", file);
			if (fmt[0] == '[')
				sprintf(LogBuf, "[%p][%s]", std::this_thread::get_id(), buf);
			else
				sprintf(LogBuf, "[%p][%s] ", std::this_thread::get_id(), buf);
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
		lock_guard<mutex> g(LogLock);
		LogFile << std::endl;
	}
}