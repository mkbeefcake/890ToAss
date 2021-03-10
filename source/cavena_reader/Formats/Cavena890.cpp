#include "Cavena890.h"
#include "../libse/FileUtil.h"
#include "../libse/Paragraph.h"
#include "../libse/Configuration.h"
#include "../libse/TimeCode.h"
#include "../libse/StringExtensions.h"
#include "../libse/Utilities.h"
#include "../../my_api.h"
#include <unistd.h>

std::unordered_map<int, std::string> Cavena890::ArabicDictionary =
{
	{0x58, "م"},
	{0x41, "ا"},
	{0x4e, "ص"},
	{0x42, "ب"},
	{0x46, "ح"},
	{0x57, "ل"},
	{0x47, "خ"},
	{0x5d, "ي"},
	{0x4a, "ر"},
	{0x2c, "،"},
	{0x59, "ن"},
	{0x5a, "و"},
	{0x43, "ت"},
	{0x1d, "-"},
	{0x49, "ذ"},
	{0x45, "ج"},
	{0x5b, "ه"},
	{0x56, "ك"},
	{0x21, "؟"},
	{0x4c, "س"},
	{0x52, "ع"},
	{0x5c, "ة"},
	{0x5e, "ى"},
	{0x61, "أ"},
	{0x48, "د"},
	{0x4d, "ش"},
	{0x60, "ء"},
	{0x68, "ﻷ"},
	{0x54, "ف"},
	{0x55, "ق"},
	{0x22, "!"},
	{0x67, "ﻻ"},
	{0x66, "ؤ"},
	{0x64, "آ"},
	{0x50, "ط"},
	{0x6a, "ﻵ"},
	{0x4f, "ض"},
	{0x6b, "ﺋ"},
	{0x44, "ث"},
	{0x51, "ظ"},
	{0x53, "غ"},
	{0x4b, "ز"},
	{0x23, "\""},
	{0x6c, "ـ"}
};

std::vector<int> Cavena890::HebrewCodes = { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x49, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x54, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x4b, 0x4a, 0x48, 0x53, 0x55, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0x91, 0xDB, 0x93, 0xDC, 0x95, 0x96, 0x97, 0xAB, 0x99, 0x9A, 0x9B, 0x9C, 0xDD, 0xDE, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA };
std::vector<std::string> Cavena890::HebrewLetters = { "א", "ב", "ג", "ד", "ה", "ו", "ז", "ח", "י", "ל", "ם", "מ", "ן", "נ", "ס", "ע", "פ", "צ", "ק", "ר", "ש", "ת", "כ", "ך", "ט", "ף", "ץ", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
std::vector<int> Cavena890::RussianCodes = { 0x42, 0x45, 0x5A, 0x56, 0x49, 0x4E, 0x58, 0x51, 0x56, 0x53, 0x72, 0x69, 0x71, 0x6E, 0x74, 0x5C, 0x77, 0x46, 0x5E, 0x44, 0x62, 0x73, 0x75, 0x64, 0x60, 0x6A, 0x6C, 0x47, 0x78, 0x7A, 0x7E, 0x6D, 0x67, 0x79, 0x70, 0x76, 0x55, 0x7D, 0x66, 0x7C, 0x7B, 0x50, 0x52, 0x68 };

std::vector<std::string> Cavena890::RussianLetters = { "Б", "Е", "З", "В", "И", "Н", "Ы", "Я", "V", "С", "р", "и", "я", "н", "т", "Э", "ю", "Ф", "Ч", "Д", "б", "с", "у", "д", "ж", "й", "л", "Г", "ы", "з", "ч", "м", "г", "ь", "п", "в", "У", "щ", "ф", "э", "ш", "П", "Р", "х" };

/*
std::vector<std::wstring> Cavena890::RussianLetters = {L"Б", L"Е", L"З", L"В", L"И", L"Н", L"Ы", L"Я", L"V", L"С", L"р", L"и", L"я", L"н", L"т", L"Э", L"ю", L"Ф", L"Ч", L"Д", L"б", L"с", L"у", L"д", L"ж", L"й", L"л", L"Г", L"ы", L"з", L"ч", L"м", L"г", L"ь", L"п", L"в", L"У", L"щ", L"ф", L"э", L"ш", L"П", L"Р", L"х"};
*/

Cavena890::Cavena890()
{

}
std::string Cavena890::getExtension() const
{
	return ".890";
}

const std::string Cavena890::NameOfFormat = "Cavena 890";

std::string Cavena890::getName() const
{
	return NameOfFormat;
}

bool Cavena890::getIsTimeBased() const
{
	return false;
}

bool Cavena890::IsMine(const std::string &fileName)
{
	
	if (!fileName.empty()/* && FileSystem::fileExists(fileName)*/)
	{
		//auto fi = new FileInfo(fileName);
		_finddata_t fi = getFileInfo(fileName);

		//if (fi->Length >= 512 && fi->Length < 1024000) // not too small or too big
		if (fi.size >= 512 && fi.size < 1024000) // not too small or too big
		{
			//if (!fileName.substr(fileName.length() ".890", StringComparison::Ordinal))
			if (fileName.substr(fileName.length()-4) != ".890")
			{
				//delete fi;
				return false;
			}

			//delete fi;
			return SubtitleFormat::IsMine( fileName);
		}

		//delete fi;
	}
	return false;
}

std::string Cavena890::ToText(Subtitle *subtitle, const std::string &title)
{	
	// to avoid -Wunused-parameter
	UNUSED(subtitle);
	UNUSED(title);
	
	return "Not supported!";
}

bool Cavena890::probe(std::istream& istrm)
{
	u8Vector buffer = FileUtil::ReadAllStream(istrm);
	
    // printf("Cavena890::probe(): %ld\n", buffer.size());

	// step 1: file size must be 512 ~ 1024000
    if (buffer.size() < 512 || buffer.size() > 1024000)
    {
        return false;
    }

    // printf("Cavena890::probe(): PASS STEP 1\n");

	// step 2: file size must be divided by 128
	if (buffer.size() % 128 != 0)
	{
		return false;
	}
	
 	unsigned char line1 = buffer[0x92];
	unsigned char line2 = buffer[0x93];

    // printf("Cavena890::probe(): line1 = 0x%x, line2 = 0x%x \n", line1, line2);

	if ((line1 != 0x00) && (line1 != LanguageIdDanish) &&
		(line1 != LanguageIdEnglish) && (line1 != LanguageIdRussian) && 
		(line1 != LanguageIdArabic) && (line1 != LanguageIdHebrew) &&
		(line1 != LanguageIdChineseTraditional) && (line1 != LanguageIdChineseSimplified) && 
		(line1 != LanguageIdRomanian))
	{
		return false;
	}

	if ((line2 != 0x00) && (line2 != LanguageIdDanish) &&
		(line2 != LanguageIdEnglish) && (line2 != LanguageIdRussian) && 
		(line2 != LanguageIdArabic) && (line2 != LanguageIdHebrew) &&
		(line2 != LanguageIdChineseTraditional) && (line2 != LanguageIdChineseSimplified) && 
		(line2 != LanguageIdRomanian))
	{
		return false;
	}

	// printf("Cavena890::probe(): PASS STEP 2 : buffer.size = %ld\n", buffer.size());

	// step 3: 
	int blockCount = buffer.size() / 0x80;
	// unsigned short prevNumber = 0;
	// int  magicEndNumber = -1;
	for (int i=3; i<blockCount; i++)
	{
		// step 3.1 : the first 4 bytes must be zero per each 0x80 bytes from 0x180
		if (buffer[0x80*i] != 0 || buffer[0x80*i+1] != 0 ||
			buffer[0x80*i+2] != 0 || buffer[0x80*3] != 0)
		{
			printf("Cavena890::probe(): STEP 3.1 issue : i = %d \n", i);
			return false;
		}

		// printf("Cavena890::probe(): STEP 3.1 : i = %d, blockCount = %d \n", i, blockCount);

		// step 3.2 : time frame checking
		int startFrame = (int)buffer[0x80 * i + 6] * 256 * 256 + buffer[0x80 * i + 7] * 256 + buffer[0x80 * i + 8];
		int endFrame = (int)buffer[0x80 * i + 9] * 256 * 256 + buffer[0x80 * i + 10] * 256 + buffer[0x80 * i + 11];
		if (startFrame > endFrame) {
			printf("Cavena890::probe(): STEP 3.2 issue : startFrame = 0x%x, endFrame = 0x%x \n", startFrame, endFrame);
			return false;
		}
		else {
			// printf("Cavena890::probe(): STEP 3.2 : startFrame = 0x%x, endFrame = 0x%x \n", startFrame, endFrame);
		}

		// step 3.2 : increasing frame numbering.. : WRONG CONDITION
		// unsigned short frameNumber = buffer[0x80 * i + 4] * 256 + buffer[0x80 * i + 5];
		// if (prevNumber > frameNumber) 
		// {
		// 	printf("Cavena890::probe(): issue : frameNumber = %d \n", frameNumber);
		// 	return false;
		// }
		// else {
		// 	prevNumber = frameNumber;
		// }
		// printf("Cavena890::probe(): STEP 3.2 : frameNumber = %d \n", frameNumber);

		// step 3.3: same number at end of first line : WRONG CONDITION
		// int endValue =  buffer[0x80*i+12] * 256 * 256 * 256 + 
		// 				buffer[0x80*i+13] * 256 * 256 +
		// 				buffer[0x80*i+14] * 256 +
		// 				buffer[0x80*i+15];
		// if (magicEndNumber == -1) {
		// 	magicEndNumber = endValue;
		// }
		// else if (magicEndNumber != endValue)
		// {
		// 	return false;
		// }
		// printf("Cavena890::probe(): STEP 3.3 : magicNumber = %x \n", endValue);

	}

	return true;
}

Subtitle* Cavena890:: LoadSubtitle(std::istream& istrm)
{

    u8Vector buffer = FileUtil::ReadAllStream(istrm);

    //printf("stream size = %d\n", buffer.size());

    if (buffer.size() < 512 || buffer.size() > 1024000)
    {
        return 0;
    }

    Subtitle* subtitle = new Subtitle;

    constexpr int textLength = 51;

    subtitle->Paragraphs.clear();
    subtitle->Header.clear();

    _languageIdLine1 = buffer[146];
    if (_languageIdLine1 == 0)
    {
        _languageIdLine1 = LanguageIdEnglish;
    }

    _languageIdLine2 = buffer[147];
    if (_languageIdLine2 == 0)
    {
        _languageIdLine2 = LanguageIdEnglish;
    }

    auto fontNameLine1 = getASCIIString(buffer, 187, 6);
    auto fontNameLine2 = getASCIIString(buffer, 246, 6);

    // Hebrew
    if (_languageIdLine1 == LanguageIdHebrew || fontNameLine1 == "HEBNOA" || fontNameLine2 == "HEBNOA")
    {
        _languageIdLine1 = LanguageIdHebrew;
        _languageIdLine2 = LanguageIdHebrew;
    }

    // Arabic
    else if (_languageIdLine2 == LanguageIdArabic || fontNameLine1 == "ARABIC")
    {
        _languageIdLine1 = LanguageIdArabic;
        _languageIdLine2 = LanguageIdArabic;
    }

        // Russian
    else if (_languageIdLine1 == LanguageIdRussian || StringHelper::startsWith(fontNameLine1, "KYRIL") || StringHelper::startsWith(fontNameLine2, "KYRIL"))
    {
        _languageIdLine1 = LanguageIdRussian;
        _languageIdLine2 = LanguageIdRussian;
    }
        // Chinese
    else if (_languageIdLine1 == LanguageIdChineseSimplified)
    {
        _languageIdLine1 = LanguageIdChineseSimplified;
        _languageIdLine2 = LanguageIdChineseSimplified;
    }
    else if (_languageIdLine1 == LanguageIdChineseTraditional || fontNameLine1 == "CCKM44" || fontNameLine2 == "CCKM44")
    {
        _languageIdLine1 = LanguageIdChineseTraditional;
        _languageIdLine2 = LanguageIdChineseTraditional;
    }

    int i = 455;
    int lastNumber = -1;

    while (i < (int)buffer.size() - 20)
    {
		int start = i - textLength;

		int number = buffer[start - 16] * 256 + buffer[start - 15];

		auto p = new Paragraph();

		std::string line1 = Cavena890::FixText(buffer, start, textLength, _languageIdLine1);
		std::string line2 = Cavena890::FixText(buffer, start + textLength + 6, textLength, _languageIdLine2);

		if (lastNumber == number)
		{
			p = subtitle->Paragraphs[subtitle->Paragraphs.size() - 1];

			if (subtitle->Paragraphs.size() == 1)
			{
				for(auto line:StringHelper::split(p->Text, '\n'))
				{
					subtitle->Header.push_back(StringHelper::replace(line, "\r", ""));
				}
			}
			//std::string temp = (StringHelper::trimEnd(line1) + "\r\n" + line2)->TrimEnd();
			std::string temp = StringHelper::trimEnd(StringHelper::trimEnd(line1) + "\r\n" + line2);
			if (temp.length() > 0)
			{
				p->Text = temp;
			}
		}
		else
		{
			int startFrame = (int)buffer[start - 14] * 256 * 256 + buffer[start - 13] * 256 + buffer[start - 12];
			int endFrame = (int)buffer[start - 11] * 256 * 256 + buffer[start - 10] * 256 + buffer[start - 9];

			p->StartTime->setTotalMilliseconds((TimeCode::BaseUnit / Configuration::getSettings()->General->getCurrentFrameRate()) * startFrame);
			p->EndTime->setTotalMilliseconds((TimeCode::BaseUnit / Configuration::getSettings()->General->getCurrentFrameRate()) * endFrame);
			//p->Text = (StringHelper::trimEnd(line1) + "\r\n" + line2)->TrimEnd();
			
			// Modified by Anatoliy
			// p->Text = StringHelper::trimEnd(StringHelper::trimEnd(line1) + "\r\n" + line2);

			if (StringHelper::trimEnd(line1).length() == 0) {
				p->Text = StringHelper::trimEnd(line2);
			}
			else if (StringHelper::trimEnd(line2).length() == 0) {
				p->Text = StringHelper::trimEnd(line1);
			}
			else 
			{
				p->Text = StringHelper::trimEnd(StringHelper::trimEnd(line1) + "\r\n" + line2);
			}

			// printf("Here: Line1(%d), Line2(%d) \n", 
			// 	StringHelper::trimEnd(line1).length(), StringHelper::trimEnd(line2).length());
			subtitle->Paragraphs.push_back(p);
		}
		/*
		unsigned char boxType = buffer[start + textLength + 3];
		if (boxType >= 0xa0 && boxType <= 0xa9 && !p->Text.empty()) // box
		{
			if (p->Text.substr(0,2) == "{\\" && p->Text.find( "}"))
			{
				p->Text.insert((int)p->Text.find('}', 3) + 1, "<box>");
				p->Text = p->Text + "</box>";
			}
			else
			{
				p->Text = "<box>" + p->Text + "</box>";
			}
		}*/

		lastNumber = number;

		i += 128;

//C# TO C++ CONVERTER TODO TASK: A 'delete p' statement was not added since p was passed to a method or constructor. Handle memory management manually.
    }

    subtitle->Renumber();
    return subtitle;
}
#include <fstream>
void Cavena890::LoadSubtitle(Subtitle **subtitle, const std::string &fileName)
{
    std::ifstream is(fileName);
    *subtitle = LoadSubtitle(is);
}

std::string Cavena890::FixText(u8Vector& buffer, int start, int textLength, int languageId)
{
	std::string text;

	if (languageId == Cavena890::LanguageIdRussian)
	{
		//auto encoding = Encoding::GetEncoding(1252);
		setCodePage(1252);
		//auto sb = new StringBuilder();

		std::string sb;
		for (int i = 0; i < textLength; i++)
		{
			int b = buffer[start + i];
			int idx = VectorHelper::indexOf(Cavena890::RussianCodes, b);
			if (idx >= 0)
			{
				sb.append(Cavena890::RussianLetters[idx]);

			}
			else
			{
			    sb.append(getEncodedString(buffer, start + i, 1));
			}
		}

		text = sb;//->toString();
		
		text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x7F }), ""); // Used to fill empty space upto 51 bytes
		
		text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x7F }), ""); // Unknown?
		text = Cavena890::FixColors(text);

		//if (Nikse::SubtitleEdit::Core::StringExtensions::Contains(text, "<i></i>"))
		if (text.find("<i></i>"))
		{
			text = StringHelper::replace(text, "<i></i>", "<i>");
		}

		//if (Nikse::SubtitleEdit::Core::StringExtensions::Contains(text, "<i>") && !Nikse::SubtitleEdit::Core::StringExtensions::Contains(text, "</i>"))
		if (text.find("<i>") && !text.find("</i>"))
		{
			text += "</i>";
		}

		//delete sb;
	}
	else if (languageId == Cavena890::LanguageIdHebrew) // (_language == "HEBNOA")
	{
		setCodePage(1252);

		std::string sb;
        std::vector<bool> b_heb_vec;
        for (int i = 0; i < textLength; i++)
		{
			int b = buffer[start + i];
			int idx = VectorHelper::indexOf(Cavena890::HebrewCodes, b);
			if (idx >= 0)
			{
                b_heb_vec.push_back(true);
				sb.append(Cavena890::HebrewLetters[idx]);
			}
			else
			{
			    if(buffer[start + i] != 0x7F && buffer[start + i] != 0xBE)
			    {
                    b_heb_vec.push_back(false);
                    sb.append(getEncodedString(buffer, start + i, 1));
			    }

			}
		}

		text = sb;// ->toString();

		//text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x7F }), ""); // Used to fill empty space upto 51 bytes
		//text = StringHelper::replace(text, getEncodedString(u8Vector{ 0xBE }), ""); // Unknown?
		//text = Cavena890::FixColors(text);
		
		// Modified by Anatoliy
		text = Cavena890::ReverseAnsi(text, b_heb_vec);

		text = Utilities::ReverseStartAndEndingForRightToLeft(text,b_heb_vec);

		text = Utilities::FixPunctuationMarks1(text, b_heb_vec);

		//delete sb;
	}
	else if (languageId == Cavena890::LanguageIdArabic)
	{
		text = Cavena890::FixTextArabic(buffer, start, textLength);
	}
	else if (languageId == Cavena890::LanguageIdChineseTraditional || languageId == Cavena890::LanguageIdChineseSimplified) //  (_language == "CCKM44" || _language == "TVB000")
	{
		text = Cavena890::FixTextTraditional(buffer, start, textLength);
	}
	else
	{
		text = Cavena890::FixTextOtherCase(buffer, start, textLength);
	}

	return text;
}


std::string Cavena890::FixColors(const std::string& text)
{
	setCodePage(1252);
	//	Encoding *encoding = Encoding::GetEncoding(1252);
	bool fontColorOn = false;
	//auto sb = new StringBuilder();
	std::string sb;
	for (int i = 0; i < (int) text.length(); i++)
	{
		auto s = text.substr(i, 1);
		if (s == getEncodedString(u8Vector{ 0xf1 }))//"ñ")//
		{
			if (fontColorOn)
			{
				sb.append("</font>"); // white
			}
			sb.append("<font color=\"#FF797D\">"); // red
			fontColorOn = true;
		}
		else if (s == getEncodedString(u8Vector{ 0xf2 }))//"õ")//
		{
			if (fontColorOn)
			{
				sb.append("</font>"); // white
			}
			sb.append("<font color=\"#AAEF9E\">"); // green
			fontColorOn = true;
		}
		else if (s == getEncodedString(u8Vector{ 0xf3 }))//"ó")//
		{
			if (fontColorOn)
			{
				sb.append("</font>"); // white
			}
			sb.append("<font color=\"#FAFAA8\">"); // yellow
			fontColorOn = true;
		}
		else if (s == getEncodedString(u8Vector{ 0xf4 }))//"ô")//
		{
			if (fontColorOn)
			{
				sb.append("</font>"); // white
			}
			sb.append("<font color=\"#9999FF\">"); // purple
			fontColorOn = true;
		}
		else if (s == getEncodedString(u8Vector{ 0xf5 }))//"õ")//
		{
			if (fontColorOn)
			{
				sb.append("</font>"); // white
			}
			sb.append("<font color=\"#FFABFB\">"); // magenta
			fontColorOn = true;
		}
		else if (s == getEncodedString(u8Vector{ 0xf6 }))//"ö")//
		{
			if (fontColorOn)
			{
				sb.append("</font>"); // white
			}
			sb.append("<font color=\"#A2FEFE\">"); // cyan
			fontColorOn = true;
		}
		else if (s == getEncodedString(u8Vector{ 0xf7 }))//"÷")//
		{
			if (fontColorOn)
			{
				sb.append("</font>"); // white
				fontColorOn = false;
			}
		}
		else if (s == getEncodedString(u8Vector{ 0xf8 }))//"ø")//
		{
			sb.append("<font color=\"#FCC786\">"); // orange
			fontColorOn = true;
		}
		else
		{
			sb.append(s);
		}
	}
	if (fontColorOn)
	{
		sb.append("</font>"); // white
	}

	//delete sb;
	return sb;// ->toString();
}


std::string Cavena890::FixTextOtherCase(u8Vector& buffer, int start, int textLength)
{
	//auto encoding = Encoding::GetEncoding(1252); 
	setCodePage(1252);

	//std::string text = StringHelper::replace(getEncodedString(buffer, start, textLength), "\0", "");
	std::string text = getEncodedString(buffer, start, textLength);

	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x7F }), ""); // Used to fill empty space upto 51 bytes
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0xBE }), ""); // Unknown?
	text = Cavena890::FixColors(text);

	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x1B }), "æ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x1C }), "ø");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x1D }), "å");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x1E }), "Æ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x1F }), "Ø");

	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x5B }), "Æ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x5C }), "Ø");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x5D }), "Å");

	// capitals with accent grave
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x81, 0x41 }), "À");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x81, 0x45 }), "È");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x81, 0x49 }), "Ì");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x81, 0x4f }), "Ò");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x81, 0x55 }), "Ù");

	// lowercase with accent grave
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x81, 0x61 }), "à");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x81, 0x65 }), "è");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x81, 0x69 }), "ì");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x81, 0x6F }), "ò");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x81, 0x75 }), "ù");

	// capitals with accent aigu
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x41 }), "Á");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x43 }), "Ć");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x45 }), "É");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x49 }), "Í");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x4C }), "Ĺ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x4E }), "Ń");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x4F }), "Ó");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x52 }), "Ŕ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x53 }), "Ś");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x55 }), "Ú");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x57 }), "Ẃ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x59 }), "Ý");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x5A }), "Ź");

	// lowercase with accent aigu
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x61 }), "á");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x63 }), "ć");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x65 }), "é");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x69 }), "í");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x6C }), "ĺ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x6E }), "ń");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x6F }), "ó");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x72 }), "ŕ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x73 }), "ś");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x75 }), "ú");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x77 }), "ẃ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x79 }), "ý");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x82, 0x7A }), "ź");

	// capitals with accent circonflexe
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x41 }), "Â");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x43 }), "Ĉ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x45 }), "Ê");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x47 }), "Ĝ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x48 }), "Ĥ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x49 }), "Î");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x4A }), "Ĵ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x4F }), "Ô");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x53 }), "Ŝ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x55 }), "Û");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x57 }), "Ŵ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x59 }), "Ŷ");

	// lowercase with accent circonflexe
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x61 }), "â");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x63 }), "ĉ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x65 }), "ê");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x67 }), "ĝ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x68 }), "ĥ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x69 }), "î");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x6A }), "ĵ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x6F }), "ô");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x73 }), "ŝ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x75 }), "û");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x77 }), "ŵ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x83, 0x79 }), "ŷ");
	text = Cavena890::FixTextOtherCase2(text);

	return text;
}

std::string Cavena890::ReverseAnsi(const std::string& text, std::vector<bool> b_heb_vec)
{
	//auto sb = new StringBuilder();
	//auto ansi = new StringBuilder();
	std::string sb;
	std::string ansi;
	int offset = 0;

	for(auto b_is_heb:b_heb_vec)
	{
		if(b_is_heb)
		{
			if (ansi.length() > 0)
			{
				sb.append(Utilities::ReverseString(ansi));// ->toString()));				
				ansi.clear();
			}
			sb.append(1, text[offset]);
            sb.append(1, text[offset + 1]);
            offset += 2;
		}
		else
		{
			ansi.append(1, text[offset]);
			offset ++;
		}
	}
	if (ansi.length() > 0)
	{
		sb.append(Utilities::ReverseString(ansi));// .toString()));
	}

	//	delete ansi;
	//	delete sb;
	return sb;// ->toString();
}

std::string Cavena890::FixTextArabic(u8Vector& buffer, int start, int textLength)
{
	//auto encoding = Encoding::GetEncoding(1252);
	setCodePage(1252);
	//auto sb = new StringBuilder();
	std::string sb;

	for (int i = 0; i < textLength; i++)
	{
		int b = buffer[start + i];
		std::string v;
		// auto ArabicDictionary_iterator = Cavena890::ArabicDictionary.find(b);
		std::unordered_map<int, std::string>::const_iterator ArabicDictionary_iterator = Cavena890::ArabicDictionary.find(b);

		if (ArabicDictionary_iterator != Cavena890::ArabicDictionary.end())
		{
			v = ArabicDictionary_iterator->second;
			sb.append(v);
		}
		else
		{
			// CAUSE ISSUE : since iterator indicates END, so couldn't get second field
			// v = ArabicDictionary_iterator->second;

			if (b != 0x7F) // filler (decimal 127)
			{
				sb.append(getEncodedString(buffer, start + i, 1));
			}
		}
	}

	std::string text = sb;// ->toString();
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0xBE }), ""); // Unknown?
	text = StringHelper::trim(Cavena890::FixColors(text));

	//delete sb;
	return text;
}

std::string Cavena890::FixTextTraditional(u8Vector& buffer, int start, int textLength)
{
	int index = start;
	std::string text = "";

	while (textLength >= 1 && index + textLength < (int)buffer.size() && (buffer[index + textLength - 1] == 0))
	{
		textLength--;
	}

	if (textLength > 0)
	{
		//text = StringHelper::replace(getEncodedString(1201, buffer, index, textLength), "\0", "");
		text = getEncodedString(1201, buffer, index, textLength);
	}
	else
	{
		text = "";
	}

	//auto encoding = Encoding::Default; // which encoding?? Encoding.GetEncoding("ISO-8859-5")
	setCodePage(28595);
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x7F }), ""); // Used to fill empty space upto 51 bytes
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0xBE }), ""); // Unknown?
	text = Cavena890::FixColors(text);
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x88 }), "<i>");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x98 }), "</i>");

	if (text.find("<i></i>"))
	{
		text = StringHelper::replace(text, "<i></i>", "<i>");
	}

	if (text.find("<i>") && !text.find("</i>"))
	{
		text += "</i>";
	}

	return text;
}



std::string Cavena890::FixTextOtherCase2(const std::string& szText)
{
	//auto encoding = Encoding::GetEncoding(1252);
	setCodePage(1252);
	std::string text = szText;

	// capitals with caron
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x41 }), "Ǎ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x43 }), "Č");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x44 }), "Ď");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x45 }), "Ě");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x47 }), "Ǧ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x49 }), "Ǐ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x4C }), "Ľ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x4E }), "Ň");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x52 }), "Ř");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x53 }), "Š");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x54 }), "Ť");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x5A }), "Ž");

	// lowercase with caron
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x61 }), "ǎ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x63 }), "č");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x64 }), "ď");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x65 }), "ě");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x67 }), "ǧ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x69 }), "ǐ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x6C }), "ľ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x6E }), "ň");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x72 }), "ř");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x73 }), "š");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x74 }), "ť");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x84, 0x7A }), "ž");

	// capitals with tilde
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x85, 0x41 }), "Ã");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x85, 0x49 }), "Ĩ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x85, 0x4E }), "Ñ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x85, 0x4F }), "Õ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x85, 0x55 }), "Ũ");

	// lowercase with tilde
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x85, 0x61 }), "ã");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x85, 0x69 }), "ĩ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x85, 0x6E }), "ñ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x85, 0x6F }), "õ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x85, 0x75 }), "ũ");

	// capitals with trema
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x86, 0x41 }), "Ä");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x86, 0x45 }), "Ë");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x86, 0x49 }), "Ï");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x86, 0x4F }), "Ö");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x86, 0x55 }), "Ü");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x86, 0x59 }), "Ÿ");

	// lowercase with trema
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x86, 0x61 }), "ä");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x86, 0x65 }), "ë");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x86, 0x69 }), "ï");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x86, 0x6F }), "ö");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x86, 0x75 }), "ü");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x86, 0x79 }), "ÿ");

	// with ring
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x8C, 0x61 }), "å");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x8C, 0x41 }), "Å");

	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x88 }), "<i>");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x98 }), "</i>");

	// ăĂ şŞ ţŢ (romanian)
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x89, 0x61 }), "ă");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x89, 0x41 }), "Ă");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x87, 0x73 }), "ş");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x87, 0x53 }), "Ş");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x87, 0x74 }), "ţ");
	text = StringHelper::replace(text, getEncodedString(u8Vector{ 0x87, 0x54 }), "Ţ");

	if (text.find("<i></i>"))
	{
		text = StringHelper::replace(text, "<i></i>", "<i>");
	}

	if (text.find("<i>") && !text.find("</i>"))
	{
		text += "</i>";
	}

	return text;
}
