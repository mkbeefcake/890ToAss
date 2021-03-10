#include <algorithm>
#include "StringExtensions.h"

bool StringExtensions::StartsWith(const std::string &s, char c)
{
	return s.length() > 0 && s[0] == c;
}

bool StringExtensions::Contains(const std::string &source, char value)
{
	return source.find(value) != std::string::npos;
}

bool StringExtensions::EndsWith(const std::string& s, const std::string suffix)
{
	if (s.length() < suffix.length()) 
	{
		return false;
	}
	return s.substr(s.length() - suffix.length()) == suffix;
}

bool StringExtensions::StartsWith(const std::string& s, const std::string prefix)
{
	if (s.length() < prefix.length())
	{
		return false;
	}
	return s.substr(0, prefix.length()) == prefix;
}

std::vector<std::string> StringExtensions::SplitToLines(const std::string &s)
{
	//original non-optimized version: return source.Replace("\r\r\n", "\n").Replace("\r\n", "\n").Replace('\r', '\n').Replace('\u2028', '\n').Split('\n');

	auto lines = std::vector<std::string>();
	int start = 0;
	int max = s.length();
	int i = 0;
	while (i < max)
	{
		auto ch = s[i];
		if (ch == '\r')
		{
			if (i < (int) s.length() - 2 && s[i + 1] == '\r' && s[i + 2] == '\n') // \r\r\n
			{
				lines.push_back(start < i ? s.substr(start, i - start) : "");
				i += 3;
				start = i;
				continue;
			}

			if (i < (int) s.length() - 1 && s[i + 1] == '\n') // \r\n
			{
				lines.push_back(start < i ? s.substr(start, i - start) : "");
				i += 2;
				start = i;
				continue;
			}

			lines.push_back(start < i ? s.substr(start, i - start) : "");
			i++;
			start = i;
			continue;
		}

		if (ch == '\n' /*|| ch == 0x2028*/) //'\u2028'
		{
			lines.push_back(start < i ? s.substr(start, i - start) : "");
			i++;
			start = i;
			continue;
		}

		i++;
	}

	lines.push_back(start < i ? s.substr(start, i - start) : "");
	return lines;
}

std::string StringExtensions::RemoveChar(const std::string &value, char charToRemove)
{
    std::string strNewString;
    std::copy_if(value.cbegin(),
                 value.cend(),
                 std::back_inserter(strNewString),
                 [charToRemove](char c)
                 {
                    return charToRemove != c;
                 });

    return strNewString;
}

bool StringExtensions::IsOnlyControlCharactersOrWhiteSpace(const std::string &s)
{
	if (s.empty())
	{
		return true;
	}

	int max = s.length();
	for (int index = 0; index < max; index++)
	{
		auto ch = s[index];
		if (!std::iscntrl(ch) && !std::isspace(ch))
		{
			return false;
		}
	}

	return true;
}

std::string StringExtensions::RemoveControlCharactersButWhiteSpace(const std::string &s)
{
    std::string strNewString;
    std::copy_if(s.cbegin(),
                 s.cend(),
                 std::back_inserter(strNewString),
                 [](char ch)
                 {
                     return !std::iscntrl(ch) || ch == '\u000d' || ch == '\u000a' || ch == '\u0009';
                 });

    return strNewString;
}

std::string StringExtensions::PadLeft(std::string s, uint n, char c)
{
	std::string result = "";
	if (n > s.length()) 
		result.append(n - s.length(), c);

	result = result + s;
	return result;
}

std::string StringExtensions::PadRight(std::string s, uint n, char c)
{
	std::string result = "";
	if (n > s.length()) 
		result.append(n - s.length(), c);

	result = s + result;
	return result;
}
