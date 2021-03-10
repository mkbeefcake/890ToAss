#pragma once

#include <string>
#include <vector>
#include <regex>

class Utilities final
{
public:
	static const std::string WinXP2KUnicodeFontName;
	static std::vector<char> NewLineChars;

/*	static std::string UppercaseLetters;
	static std::string LowercaseLetters;
	static std::string LowercaseLettersWithNumbers;
	static std::string AllLetters;
	static std::string AllLettersAndNumbers;
	*/
	static const std::string PrePostStringsToReverse;

public:
	static std::string ReverseString(const std::string& s);

	static std::string ReverseStartAndEndingForRightToLeftD(const std::string& s, std::vector<bool> b_heb_vec);

	static std::string ReverseStartAndEndingForRightToLeft(const std::string &s, std::vector<bool> b_heb_vec);

	static std::string FixEnglishTextInRightToLeftLanguage(const std::string &text, const std::string &reverseChars);
	
	static std::string FixEnglishTextInRightToLeftLanguageD(const std::string& text, const std::string& reverseChars);

	static std::string ReverseParenthesis(const std::string& s);

	static std::string FixPunctuationMarks1(const std::string& s, std::vector<bool> b_heb_vec);

	static std::string ReverseOnlyNumAndChar(const std::string& s);
};
