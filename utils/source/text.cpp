#include "text.h"
#include <sstream>

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
	std::istringstream isstr(text);
	std::ostringstream osstr;
	std::string word;
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