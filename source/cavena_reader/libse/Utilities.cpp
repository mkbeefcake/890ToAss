#include "Utilities.h"
#include "StringExtensions.h"
#include "../../common/stringhelper.h"
#include "../../common/define.h"

const std::string Utilities::WinXP2KUnicodeFontName = "Times New Roman";
std::vector<char> Utilities::NewLineChars = {'\r', '\n'};
/*//C# TO C++ CONVERTER TODO TASK: There is no direct C++ equivalent to this .NET String method:
std::string Utilities::UppercaseLetters = Configuration::getSettings()->General->getUppercaseLetters().ToUpperInvariant();
//C# TO C++ CONVERTER TODO TASK: There is no direct C++ equivalent to this .NET String method:
std::string Utilities::LowercaseLetters = Configuration::getSettings()->General->getUppercaseLetters().ToLowerInvariant();
std::string Utilities::LowercaseLettersWithNumbers = LowercaseLetters + "0123456789";
std::string Utilities::AllLetters = UppercaseLetters + LowercaseLetters;
std::string Utilities::AllLettersAndNumbers = UppercaseLetters + LowercaseLettersWithNumbers;
*/
std::string Utilities::ReverseStartAndEndingForRightToLeft(const std::string &s, std::vector<bool> b_heb_vec)
{
	return ReverseStartAndEndingForRightToLeftD(s,b_heb_vec);
}

std::string Utilities::FixEnglishTextInRightToLeftLanguage(const std::string &text, const std::string &reverseChars)
{
	return FixEnglishTextInRightToLeftLanguageD(text, reverseChars);
}

std::string Utilities::FixEnglishTextInRightToLeftLanguageD(const std::string& text, const std::string& reverseChars)
{
	//auto sb = new StringBuilder();
	std::string sb;
	auto lines = StringExtensions::SplitToLines(text);
	for (auto line : lines)
	{
		//std::string s = ReverseParenthesis(line.Trim());
		std::string s = ReverseParenthesis(StringHelper::trim(line));
		bool numbersOn = false;
		std::string numbers = "";
		for (int i = 0; i < (int) s.length(); i++)
		{
			if (numbersOn && StringExtensions::Contains(reverseChars, s[i]))
			{
				numbers = StringHelper::toString(s[i]) + numbers;
			}
			else if (numbersOn)
			{
				numbersOn = false;
				s.erase(i - numbers.length(), numbers.length());
				s.insert(i - numbers.length(), numbers);
				numbers = "";
			}
			else if (StringExtensions::Contains(reverseChars, s[i]))
			{
				numbers = StringHelper::toString(s[i]) + numbers;
				numbersOn = true;
			}
		}
		if (numbersOn)
		{
			int i = s.length();
			s.erase(i - numbers.length(), numbers.length());
			s.insert(i - numbers.length(), numbers);
		}

		sb += s + "\n";
	}

	//delete sb;
	//return sb->toString()->Trim();
	return StringHelper::trim(sb);
}

std::string Utilities::ReverseParenthesis(const std::string& s)
{
	if (s.empty())
	{
		return s;
	}
	int len = s.length();
	auto chars = std::vector<char>(len + 1);
	for (int i = 0; i < len; i++)
	{
		char ch = s[i];
		switch (ch)
		{
		case '(':
			ch = ')';
			break;
		case ')':
			ch = '(';
			break;
		case '[':
			ch = ']';
			break;
		case ']':
			ch = '[';
			break;
		}
		chars[i] = ch;
	}
	chars[len] = 0;
	//return std::string(chars);
	return std::string(chars.data());
}
const std::string Utilities::PrePostStringsToReverse = R"(-— !?.…"،,():;[]+~*/<>&^%$#\\|')";

std::string Utilities::ReverseString(const std::string& s)
{

	int len = s.length();
	if (len <= 1)
	{
		return s;
	}
	auto chars = std::vector<char>(len + 1);
	for (int i = 0; i < len; i++)
	{
		chars[i] = s[len - i - 1];
	}
	chars[len] = 0;
	//return std::string(chars);
	return std::string(chars.data());
}

std::string Utilities::ReverseStartAndEndingForRightToLeftD(const std::string& s, std::vector<bool> b_heb_vec)
{
	//KHJ/////

	//	auto newLines = new StringBuilder();
	//	auto pre = new StringBuilder();
	//	auto post = new StringBuilder();
	//	auto preTags = new StringBuilder();

	std::string newLines;
	std::string pre;
	std::string post;
	std::string preTags;

	int end_offset = s.length();
	int ii = b_heb_vec.size();

	for(ii = b_heb_vec.size()-1; ii >= 0; ii --)
	{

	    if ((b_heb_vec[ii] == false))
	    {
            char c = s[--end_offset];

			// added by Anatoliy
			if ((c >= 'a' && c <= 'z') || 
				(c >= 'A' && c <= 'Z') || 
				(c >= '0' && c <= '9')) 
			{
				end_offset++; break;
			}

			// Modified by Anatoliy
            if(c == '.' || c== ',' || c== '?' || c == ';' ||
			   c == ':' || c == '\"' || c == '!' || c == '-' || 
			   c == '\'' )
            {
                newLines += c;
            }
			else 
			{
				// HERE ARE SOMETHING
			}
	    }
	    else
	    {
	        break;
	    }
	}

	std::string str_append;
	int st_offset = 0;
    for(int i = 0; i < ii; i ++)
    {		
        if((b_heb_vec[i] == false))
        {
            char c = s[st_offset ++];
            if(c != ' ' && c != '\n' && c != '\t' && c != '\r')
            {
				// added by Anatoliy
				if ((c >= 'a' && c <= 'z') || 
					(c >= 'A' && c <= 'Z') || 
					(c >= '0' && c <= '9')) 
				{
					st_offset--; break;
				}

				// Modified by Anatoliy
				if(c == '.' || c== ',' || c== '?' || c == ';' || 
				   c == ':' || c == '\"' || c == '!' || c == '-'|| 
			   	   c == '\'')
				{
                    str_append += c;
				}
                else
                {
                    break;
                }
            }
			else
			{
				// HRE ARE SOMETHING
			}
        }
        else
        {
            break;
        }
    }
	for(int i = st_offset; i < end_offset; i++)
	{
        newLines += s[i];
	}

    newLines += str_append;
	return newLines;
	
	// auto lines = StringExtensions::SplitToLines(s);

	// for (auto line : lines)
	// {
	// 	std::string s2 = line;

	// 	preTags.clear();
	// 	//while (s2.StartsWith("{\\", StringComparison::Ordinal) && (int)s2.find('}') > 0)
	// 	while (StringExtensions::StartsWith(s2, "{\\") && (int)s2.find('}') > 0)
	// 	{
	// 		int end = (int)s2.find('}') + 1;
	// 		preTags += s2.substr( end);
	// 		s2.erase(0, end);
	// 	}
	// 	std::string postTags = "";
	// 	for (int k = 0; k < 10; k++)
	// 	{
	// 		if (StringExtensions::StartsWith(s2, "♪ ") || StringExtensions::StartsWith(s2, "♫ "))
	// 		{
	// 			preTags += s2.substr(2);
	// 			s2.erase(0, 2);
	// 		}
	// 		if (StringExtensions::StartsWith(s2, "♪") || StringExtensions::StartsWith(s2, "♫"))
	// 		{
	// 			preTags += s2.substr(1);
	// 			s2.erase(0, 1);
	// 		}
	// 		if (StringExtensions::StartsWith(s2, "<i>") || StringExtensions::StartsWith(s2, "<b>") || StringExtensions::StartsWith(s2, "<u>"))
	// 		{
	// 			preTags += s2.substr(3);
	// 			s2.erase(0, 3);
	// 		}
	// 		if (StringExtensions::StartsWith(s2, "<font ") && (int)s2.find('>') > 0)
	// 		{
	// 			int idx = (int)s2.find('>');
	// 			idx++;
	// 			preTags += s2.substr(idx);
	// 			s2.erase(0, idx);
	// 		}

			
	// 		if (StringExtensions::EndsWith( s2, " ♪") || StringExtensions::EndsWith(s2, " ♫"))
	// 		{
	// 			postTags = s2.substr(s2.length() - 2) + postTags;
	// 			s2.erase(s2.length() - 2);
	// 		}
	// 		if (StringExtensions::EndsWith(s2, "♪") || StringExtensions::EndsWith(s2, "♫"))
	// 		{
	// 			postTags = s2.substr(s2.length() - 1) + postTags;
	// 			s2.erase(s2.length() - 1);
	// 		}
	// 		if (StringExtensions::EndsWith(s2, "</i>") || StringExtensions::EndsWith(s2, "</b>") || StringExtensions::EndsWith(s2, "</u>"))
	// 		{
	// 			postTags = s2.substr(s2.length() - 4) + postTags;
	// 			s2.erase(s2.length() - 4);
	// 		}
	// 		if (StringExtensions::EndsWith(s2, "</font>"))
	// 		{
	// 			postTags = s2.substr(s2.length() - 7) + postTags;
	// 			s2.erase(s2.length() - 7);
	// 		}
	// 	}

	// 	pre.clear();
	// 	post.clear();
	// 	int i = 0;
	// 	std::string str_tmp;
	// 	while (	i < (int)s2.length() && 
	// 		StringExtensions::Contains(PrePostStringsToReverse, s2[i]) && 
	// 		s2[i] != '{' && 
	// 		!(str_tmp = s2.substr(i), StringExtensions::EndsWith(s2, "<i>")) && 
	// 		!(str_tmp = s2.substr(i), StringExtensions::StartsWith(s2, "<b>")) && 
	// 		!(str_tmp = s2.substr(i), StringExtensions::StartsWith(s2, "<font "))
	// 		)
	// 	{
	// 		pre += s2[i];
	// 		i++;
	// 	}
	// 	int j = s2.length() - 1;
	// 	while (j > i && 
	// 		StringExtensions::Contains(PrePostStringsToReverse, s2[j]) && 
	// 		s2[j] != '}' && 
	// 		!(str_tmp = s2.substr(j + 1), StringExtensions::EndsWith(s2, "</i>")) && 
	// 		!(str_tmp = s2.substr(j + 1), StringExtensions::EndsWith(s2, "</b>")) && 
	// 		!(str_tmp = s2.substr(j + 1), StringExtensions::EndsWith(s2, "</font>"))
	// 	)
	// 	{
	// 		post += s2[j];
	// 		j--;
	// 	}

	// 	newLines += preTags;
	// 	newLines += Utilities::ReverseParenthesis(post);
	// 	newLines += s2.substr(pre.length(), s2.length() - (pre.length() + post.length()));
	// 	newLines += Utilities::ReverseParenthesis(ReverseString(pre));
	// 	newLines += postTags;
	// 	newLines += "\n";
	// }

	// //std::string szRet = newLines->toString()->Trim();
	// std::string szRet = StringHelper::trim(newLines);
	// return szRet;

}

std::string Utilities::FixPunctuationMarks1(const std::string& s, std::vector<bool> b_heb_vec)
{
	std::regex e1 (" ,");
	std::regex e2 ("- \\?");
	std::regex e3 ("- \\.");
	std::regex e4 (" \\.");

	std::string result = std::regex_replace (s, e1, ", ");
	result = std::regex_replace(result, e2, "? -");
	result = std::regex_replace(result, e3, ". -");
	result = std::regex_replace(result, e4, ". ");

	// to avoid -Wunused-parameter
	UNUSED(b_heb_vec);
	return result;
}

std::string Utilities::ReverseOnlyNumAndChar(const std::string& s)
{
	int len = s.length();
	if (len <= 1)
	{
		return s;
	}

	// HERE I AM
	auto chars = std::vector<char>(len + 1);

	std::string numAndCharString = "";
	bool bDetect = false;
	int  startPos = -1;

	for (int i = 0; i < len; i++)
	{
		if ((s[i] >= '0' && s[i] <= '9') || 
			(s[i] >= 'a' && s[i] <= 'z') ||
			(s[i] >= 'A' && s[i] <= 'Z'))
		{
			if (bDetect == false) {
				bDetect = true; startPos = i;
			}
			numAndCharString.append(&s[i], 1);
		}
		else 
		{
			if (bDetect == true) {
				std::string temp = Utilities::ReverseString(numAndCharString);
				for (int j=0; j < (int)temp.length(); j++) {
					chars[startPos + j] = temp[j];
				}

				bDetect = false; startPos = -1; numAndCharString = "";
			}

			chars[i] = s[i];
		}
	}
	chars[len] = 0;
	return std::string(chars.data());
}
