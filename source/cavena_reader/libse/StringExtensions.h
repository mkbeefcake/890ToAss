#pragma once

#include <string>
#include <vector>
#include <cctype>

class StringExtensions final
{
public:
	static bool StartsWith(const std::string &s, char c);
	static bool EndsWith(const std::string& s, const std::string suffix);
	static bool StartsWith(const std::string& s, const std::string prefix);
	static bool Contains(const std::string &source, char value);

	static std::vector<std::string> SplitToLines(const std::string &s);

	static std::string RemoveChar(const std::string &value, char charToRemove);

	static bool IsOnlyControlCharactersOrWhiteSpace(const std::string &s);

	static std::string RemoveControlCharactersButWhiteSpace(const std::string &s);

	static std::string PadLeft(std::string s, uint n, char c);
	static std::string PadRight(std::string s, uint n, char c);

};
