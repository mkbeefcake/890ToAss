#include "Pac.h"
#include "../libse/FileUtil.h"
#include "../libse/Configuration.h"
#include "../../common/define.h"
#include "../libse/LanguageAutoDetect.h"
#include "../libse/Utilities.h"
#include "../libse/StringExtensions.h"
#include "../../my_api.h"
#include "../libse/Paragraph.h"
#include <fstream>

Pac *Pac::s_This = nullptr;
int Pac::CodePageLatin = 0;
int Pac::CodePageGreek = 1;
int Pac::CodePageLatinCzech = 2;
int Pac::CodePageArabic = 3;
int Pac::CodePageHebrew = 4;
int Pac::CodePageThai = 5;
int Pac::CodePageCyrillic = 6;
int Pac::CodePageChineseTraditional = 7;
int Pac::CodePageChineseSimplified = 8;
int Pac::CodePageKorean = 9;
int Pac::CodePageJapanese = 10;
int Pac::CodePageLatinTurkish = 11;

int Pac::EncodingChineseSimplified = 936;
int Pac::EncodingChineseTraditional = 950;
int Pac::EncodingKorean = 949;
int Pac::EncodingJapanese = 932;
int Pac::EncodingThai = 620;


Pac::Pac()
{
	s_This = this;
	Pac::InitializeVariables();
}

IGetPacEncoding *Pac::GetPacEncodingImplementation;
TimeCode *Pac::PacNullTime = new TimeCode(655, 35, 00, 0);
bool Pac::ThrowOnError = false;

int Pac::getCodePage() const
{
	return CodePage;
}

void Pac::setCodePage(int value)
{
	CodePage = value;
}

std::string Pac::getExtension() const
{
	return ".pac";
}

const std::string Pac::NameOfFormat = "PAC (Screen Electronics)";

std::string Pac::getName() const
{
	return NameOfFormat;
}

bool Pac::IsMine(const std::string &fileName)
{
	//if (!fileName.empty() && FileSystem::fileExists(fileName))
	if (!fileName.empty())//&& FileSystem::fileExists(fileName))
	{
		try
		{
			//auto fi = new FileInfo(fileName);
			_finddata_t fi = getFileInfo(fileName);
			//if (fi->Length > 65 && fi->Length < 1024000) // not too small or too big
			if (fi.size > 65 && fi.size < 1024000) // not too small or too big
			{
				u8Vector buffer = FileUtil::ReadAllBytesShared(fileName);

				if (buffer[00] == 1 && buffer[01] == 0 && buffer[02] == 0 && buffer[03] == 0 && buffer[04] == 0 && buffer[05] == 0 && buffer[06] == 0 && buffer[07] == 0 && buffer[8] == 0 && buffer[9] == 0 && buffer[10] == 0 && buffer[11] == 0 && buffer[12] == 0 && buffer[13] == 0 && buffer[14] == 0 && buffer[15] == 0 && buffer[16] == 0 && buffer[17] == 0 && buffer[18] == 0 && buffer[19] == 0 && buffer[20] == 0 && (buffer[23] >= 0x60 && buffer[23] <= 0x70) && StringHelper::endsWith(StringHelper::toLower(fileName), ".pac"))
				{
					//delete fi;
					return true;
				}
			}

			//delete fi;
		}
		catch (...)
		{
			return false;
		}
	}
	return false;
}

Subtitle* Pac::LoadSubtitle(std::istream& isrm)
{
    u8Vector buffer = FileUtil::ReadAllStream(isrm);
    Subtitle* subtitle = new Subtitle();
    Pac::LoadSubtitle(subtitle, buffer);
    return subtitle;
}

void Pac::LoadSubtitle(Subtitle **subtitle, const std::string &fileName)
{
	_fileName = fileName;
	std::ifstream is(fileName);

	*subtitle = LoadSubtitle(is);
}

std::string Pac::ToText(Subtitle *subtitle, const std::string &title)
{
	// to avoid -Wunused-parameter
	UNUSED(subtitle);
	UNUSED(title);
	return "Not supported!";
}


void Pac::AddArabicCodes()
{
	Pac::ArabicCodes.emplace(0xe081, SpecialCharacter("أ"));
	Pac::ArabicCodes.emplace(0xe086, SpecialCharacter("ځ"));
	Pac::ArabicCodes.emplace(0xe09b, SpecialCharacter("ؤ"));
	Pac::ArabicCodes.emplace(0xe09c, SpecialCharacter("ئ"));
	Pac::ArabicCodes.emplace(0xe181, SpecialCharacter("إ"));
	Pac::ArabicCodes.emplace(0xe281, SpecialCharacter("آ"));
	Pac::ArabicCodes.emplace(0xe781, SpecialCharacter("اً"));
	Pac::ArabicCodes.emplace(0x80, SpecialCharacter("ـ"));
	Pac::ArabicCodes.emplace(0x81, SpecialCharacter("ا"));
	Pac::ArabicCodes.emplace(0x82, SpecialCharacter("ب"));
	Pac::ArabicCodes.emplace(0x83, SpecialCharacter("ت"));
	Pac::ArabicCodes.emplace(0x84, SpecialCharacter("ث"));
	Pac::ArabicCodes.emplace(0x85, SpecialCharacter("ج"));
	Pac::ArabicCodes.emplace(0x86, SpecialCharacter("ح"));
	Pac::ArabicCodes.emplace(0x87, SpecialCharacter("خ"));
	Pac::ArabicCodes.emplace(0x88, SpecialCharacter("د"));
	Pac::ArabicCodes.emplace(0x89, SpecialCharacter("ذ"));
	Pac::ArabicCodes.emplace(0x8A, SpecialCharacter("ر"));
	Pac::ArabicCodes.emplace(0x8b, SpecialCharacter("ز"));
	Pac::ArabicCodes.emplace(0x8c, SpecialCharacter("س"));
	Pac::ArabicCodes.emplace(0x8d, SpecialCharacter("ش"));
	Pac::ArabicCodes.emplace(0x8e, SpecialCharacter("ص"));
	Pac::ArabicCodes.emplace(0x8f, SpecialCharacter("ض"));
	Pac::ArabicCodes.emplace(0x90, SpecialCharacter("ظ"));
	Pac::ArabicCodes.emplace(0x91, SpecialCharacter("ط"));
	Pac::ArabicCodes.emplace(0x92, SpecialCharacter("ع"));
	Pac::ArabicCodes.emplace(0x93, SpecialCharacter("غ"));
	Pac::ArabicCodes.emplace(0x94, SpecialCharacter("ف"));
	Pac::ArabicCodes.emplace(0x95, SpecialCharacter("ق"));
	Pac::ArabicCodes.emplace(0x96, SpecialCharacter("ك"));
	Pac::ArabicCodes.emplace(0x97, SpecialCharacter("ل"));
	Pac::ArabicCodes.emplace(0x98, SpecialCharacter("م"));
	Pac::ArabicCodes.emplace(0x99, SpecialCharacter("ن"));
	Pac::ArabicCodes.emplace(0x9A, SpecialCharacter("ه"));
	Pac::ArabicCodes.emplace(0x9b, SpecialCharacter("و"));
	Pac::ArabicCodes.emplace(0x9c, SpecialCharacter("ى"));
	Pac::ArabicCodes.emplace(0x9d, SpecialCharacter("ة"));
	Pac::ArabicCodes.emplace(0x9e, SpecialCharacter("لا"));
	Pac::ArabicCodes.emplace(0x9f, SpecialCharacter("ي"));
	Pac::ArabicCodes.emplace(0xe09f, SpecialCharacter("ي"));
	Pac::ArabicCodes.emplace(0xa0, SpecialCharacter("ء"));
	Pac::ArabicCodes.emplace(0xad, SpecialCharacter("ڪ"));
	Pac::ArabicCodes.emplace(0xae, SpecialCharacter("ﺭ"));
	Pac::ArabicCodes.emplace(0xb0, SpecialCharacter("ﺩ"));
	Pac::ArabicCodes.emplace(0xb1, SpecialCharacter("ﯼ"));
	Pac::ArabicCodes.emplace(0xb3, SpecialCharacter("۔"));
	Pac::ArabicCodes.emplace(0x3f, SpecialCharacter("؟"));
	Pac::ArabicCodes.emplace(0x25, SpecialCharacter("٪"));
	Pac::ArabicCodes.emplace(0x2c, SpecialCharacter("،"));
	Pac::ArabicCodes.emplace(0x3b, SpecialCharacter("؛"));
	Pac::ArabicCodes.emplace(0xe7, SpecialCharacter("\u064B", true));
	Pac::ArabicCodes.emplace(0xea, SpecialCharacter("\u064C", true));
	Pac::ArabicCodes.emplace(0xe8, SpecialCharacter("\u064D", true));
	Pac::ArabicCodes.emplace(0xe5, SpecialCharacter("\u064E", true));
	Pac::ArabicCodes.emplace(0xe4, SpecialCharacter("\u064F", true));
	Pac::ArabicCodes.emplace(0xe6, SpecialCharacter("\u0650", true));
	Pac::ArabicCodes.emplace(0xe3, SpecialCharacter("\u0651", true));
	Pac::ArabicCodes.emplace(0xe9, SpecialCharacter("\u0652", true));
	Pac::ArabicCodes.emplace(0xe2, SpecialCharacter("\u0653", true));
	Pac::ArabicCodes.emplace(0xe0, SpecialCharacter("\u0654", true));
	Pac::ArabicCodes.emplace(0xe1, SpecialCharacter("\u0655", true));
}


SpecialCharacter::SpecialCharacter(const std::string& character, bool switchOrder, int priority)
{
	Character = character;
	SwitchOrder = switchOrder;
	Priority = priority;
}

std::unordered_map<int, SpecialCharacter> Pac::LatinCodes;
std::unordered_map<int, SpecialCharacter> Pac::LatinTurkishOverrides;
std::unordered_map<int, SpecialCharacter> Pac::HebrewCodes;
std::unordered_map<int, SpecialCharacter> Pac::ArabicCodes;
std::unordered_map<int, SpecialCharacter> Pac::CyrillicCodes;
std::unordered_map<int, SpecialCharacter> Pac::KoreanCodes =
{
{0x20, SpecialCharacter(" ")}
};
std::unordered_map<int, SpecialCharacter> Pac::GreekCodes;

void Pac::InitializeVariables()
{
	LatinCodes.clear();
	Pac::AddLatinCodes1();
	Pac::AddLatinCodes2();
	Pac::AddLatinCodes3();
	Pac::AddLatinCodes4();

	LatinTurkishOverrides.clear();
	Pac::AddTurkishLatinCodes();

	HebrewCodes.clear();
	Pac::AddHebrewCode();
	Pac::AddCyrillicCodes3();

	ArabicCodes.clear();
	Pac::AddArabicCodes();

	CyrillicCodes.clear();
	Pac::AddCyrillicCodes1();
	Pac::AddCyrillicCodes2();

	GreekCodes.clear();
	Pac::AddGreekCodes1();
	Pac::AddGreekCodes2();
	Pac::AddGreekCodes3();
}

void Pac::AddCyrillicCodes1()
{
	Pac::CyrillicCodes.emplace(0x20, SpecialCharacter(" "));
	Pac::CyrillicCodes.emplace(0x21, SpecialCharacter("!"));
	Pac::CyrillicCodes.emplace(0x22, SpecialCharacter("Э"));
	Pac::CyrillicCodes.emplace(0x23, SpecialCharacter("/"));
	Pac::CyrillicCodes.emplace(0x24, SpecialCharacter("?"));
	Pac::CyrillicCodes.emplace(0x25, SpecialCharacter(":"));
	Pac::CyrillicCodes.emplace(0x26, SpecialCharacter("."));
	Pac::CyrillicCodes.emplace(0x27, SpecialCharacter("э"));
	Pac::CyrillicCodes.emplace(0x28, SpecialCharacter("("));
	Pac::CyrillicCodes.emplace(0x29, SpecialCharacter(")"));
	Pac::CyrillicCodes.emplace(0x2a, SpecialCharacter(";"));
	Pac::CyrillicCodes.emplace(0x2b, SpecialCharacter("+"));
	Pac::CyrillicCodes.emplace(0x2c, SpecialCharacter("б"));
	Pac::CyrillicCodes.emplace(0x2d, SpecialCharacter("-"));
	Pac::CyrillicCodes.emplace(0x2e, SpecialCharacter("ю"));
	Pac::CyrillicCodes.emplace(0x3a, SpecialCharacter("Ж"));
	Pac::CyrillicCodes.emplace(0x3b, SpecialCharacter("ж"));
	Pac::CyrillicCodes.emplace(0x3c, SpecialCharacter("<"));
	Pac::CyrillicCodes.emplace(0x3d, SpecialCharacter("="));
	Pac::CyrillicCodes.emplace(0x3e, SpecialCharacter(">"));
	Pac::CyrillicCodes.emplace(0x41, SpecialCharacter("Ф"));
	Pac::CyrillicCodes.emplace(0x42, SpecialCharacter("И"));
	Pac::CyrillicCodes.emplace(0x43, SpecialCharacter("С"));
	Pac::CyrillicCodes.emplace(0x44, SpecialCharacter("В"));
	Pac::CyrillicCodes.emplace(0x45, SpecialCharacter("У"));
	Pac::CyrillicCodes.emplace(0x46, SpecialCharacter("А"));
	Pac::CyrillicCodes.emplace(0x47, SpecialCharacter("П"));
	Pac::CyrillicCodes.emplace(0x48, SpecialCharacter("Р"));
	Pac::CyrillicCodes.emplace(0x49, SpecialCharacter("Ш"));
	Pac::CyrillicCodes.emplace(0x4a, SpecialCharacter("О"));
	Pac::CyrillicCodes.emplace(0x4b, SpecialCharacter("Л"));
	Pac::CyrillicCodes.emplace(0x4c, SpecialCharacter("Д"));
	Pac::CyrillicCodes.emplace(0x4d, SpecialCharacter("Ь"));
	Pac::CyrillicCodes.emplace(0x4e, SpecialCharacter("Т"));
	Pac::CyrillicCodes.emplace(0x4f, SpecialCharacter("Щ"));
	Pac::CyrillicCodes.emplace(0x50, SpecialCharacter("З"));
	Pac::CyrillicCodes.emplace(0x51, SpecialCharacter("Q"));
	Pac::CyrillicCodes.emplace(0x52, SpecialCharacter("К"));
	Pac::CyrillicCodes.emplace(0x53, SpecialCharacter("Ы"));
	Pac::CyrillicCodes.emplace(0x54, SpecialCharacter("Е"));
	Pac::CyrillicCodes.emplace(0x55, SpecialCharacter("Г"));
	Pac::CyrillicCodes.emplace(0x56, SpecialCharacter("М"));
	Pac::CyrillicCodes.emplace(0x57, SpecialCharacter("Ц"));
	Pac::CyrillicCodes.emplace(0x58, SpecialCharacter("Ч"));
	Pac::CyrillicCodes.emplace(0x59, SpecialCharacter("Н"));
	Pac::CyrillicCodes.emplace(0x5a, SpecialCharacter("Я"));
	Pac::CyrillicCodes.emplace(0x5b, SpecialCharacter("х"));
	Pac::CyrillicCodes.emplace(0x5d, SpecialCharacter("ъ"));
	Pac::CyrillicCodes.emplace(0x5e, SpecialCharacter(","));
	Pac::CyrillicCodes.emplace(0x5f, SpecialCharacter("-"));
	Pac::CyrillicCodes.emplace(0x61, SpecialCharacter("ф"));
	Pac::CyrillicCodes.emplace(0x62, SpecialCharacter("и"));
	Pac::CyrillicCodes.emplace(0x63, SpecialCharacter("с"));
	Pac::CyrillicCodes.emplace(0x64, SpecialCharacter("в"));
	Pac::CyrillicCodes.emplace(0x65, SpecialCharacter("у"));
	Pac::CyrillicCodes.emplace(0x66, SpecialCharacter("а"));
	Pac::CyrillicCodes.emplace(0x67, SpecialCharacter("п"));
	Pac::CyrillicCodes.emplace(0x68, SpecialCharacter("р"));
	Pac::CyrillicCodes.emplace(0x69, SpecialCharacter("ш"));
	Pac::CyrillicCodes.emplace(0x6a, SpecialCharacter("о"));
	Pac::CyrillicCodes.emplace(0x6b, SpecialCharacter("л"));
	Pac::CyrillicCodes.emplace(0x6c, SpecialCharacter("д"));
	Pac::CyrillicCodes.emplace(0x6d, SpecialCharacter("ь"));
	Pac::CyrillicCodes.emplace(0x6e, SpecialCharacter("т"));
	Pac::CyrillicCodes.emplace(0x6f, SpecialCharacter("щ"));
	Pac::CyrillicCodes.emplace(0x70, SpecialCharacter("з"));
	Pac::CyrillicCodes.emplace(0x72, SpecialCharacter("к"));
	Pac::CyrillicCodes.emplace(0x73, SpecialCharacter("ы"));
	Pac::CyrillicCodes.emplace(0x74, SpecialCharacter("е"));
	Pac::CyrillicCodes.emplace(0x75, SpecialCharacter("г"));
	Pac::CyrillicCodes.emplace(0x76, SpecialCharacter("м"));
	Pac::CyrillicCodes.emplace(0x77, SpecialCharacter("ц"));
	Pac::CyrillicCodes.emplace(0x78, SpecialCharacter("ч"));
	Pac::CyrillicCodes.emplace(0x79, SpecialCharacter("н"));
	Pac::CyrillicCodes.emplace(0x7a, SpecialCharacter("я"));
	Pac::CyrillicCodes.emplace(0x7b, SpecialCharacter("Х"));
	Pac::CyrillicCodes.emplace(0x7d, SpecialCharacter("Ъ"));
	Pac::CyrillicCodes.emplace(0x80, SpecialCharacter("Б"));
	Pac::CyrillicCodes.emplace(0x81, SpecialCharacter("Ю"));
	Pac::CyrillicCodes.emplace(0x82, SpecialCharacter("Ђ"));
	Pac::CyrillicCodes.emplace(0x84, SpecialCharacter("Є"));
	Pac::CyrillicCodes.emplace(0x85, SpecialCharacter("Ѕ"));
	Pac::CyrillicCodes.emplace(0x86, SpecialCharacter("І"));
	Pac::CyrillicCodes.emplace(0x88, SpecialCharacter("Ј"));
	Pac::CyrillicCodes.emplace(0x89, SpecialCharacter("Љ"));
	Pac::CyrillicCodes.emplace(0x8a, SpecialCharacter("Њ"));
	Pac::CyrillicCodes.emplace(0x8b, SpecialCharacter("Ћ"));
	Pac::CyrillicCodes.emplace(0x8c, SpecialCharacter("Ґ"));
	Pac::CyrillicCodes.emplace(0x8d, SpecialCharacter("ґ"));
	Pac::CyrillicCodes.emplace(0x8f, SpecialCharacter("Џ"));
	Pac::CyrillicCodes.emplace(0x90, SpecialCharacter("№"));
	Pac::CyrillicCodes.emplace(0x92, SpecialCharacter("ђ"));
	Pac::CyrillicCodes.emplace(0x94, SpecialCharacter("є"));
	Pac::CyrillicCodes.emplace(0x95, SpecialCharacter("ѕ"));
	Pac::CyrillicCodes.emplace(0x96, SpecialCharacter("і"));
}

void Pac::AddCyrillicCodes2()
{
	Pac::CyrillicCodes.emplace(0x98, SpecialCharacter("ј"));
	Pac::CyrillicCodes.emplace(0x99, SpecialCharacter("љ"));
	Pac::CyrillicCodes.emplace(0x9a, SpecialCharacter("њ"));
	Pac::CyrillicCodes.emplace(0x9b, SpecialCharacter("ћ"));
	Pac::CyrillicCodes.emplace(0x9d, SpecialCharacter("§"));
	Pac::CyrillicCodes.emplace(0x9f, SpecialCharacter("џ"));
	Pac::CyrillicCodes.emplace(0xa2, SpecialCharacter("%"));
	Pac::CyrillicCodes.emplace(0xa4, SpecialCharacter("&"));
	Pac::CyrillicCodes.emplace(0xac, SpecialCharacter("C"));
	Pac::CyrillicCodes.emplace(0xad, SpecialCharacter("D"));
	Pac::CyrillicCodes.emplace(0xae, SpecialCharacter("E"));
	Pac::CyrillicCodes.emplace(0xaf, SpecialCharacter("F"));
	Pac::CyrillicCodes.emplace(0xb0, SpecialCharacter("G"));
	Pac::CyrillicCodes.emplace(0xb1, SpecialCharacter("H"));
	Pac::CyrillicCodes.emplace(0xb2, SpecialCharacter("'"));
	Pac::CyrillicCodes.emplace(0xb3, SpecialCharacter("\""));
	Pac::CyrillicCodes.emplace(0xb4, SpecialCharacter("I"));
	Pac::CyrillicCodes.emplace(0xb5, SpecialCharacter("J"));
	Pac::CyrillicCodes.emplace(0xb6, SpecialCharacter("K"));
	Pac::CyrillicCodes.emplace(0xb7, SpecialCharacter(""));
	Pac::CyrillicCodes.emplace(0xb8, SpecialCharacter("M"));
	Pac::CyrillicCodes.emplace(0xb9, SpecialCharacter("N"));
	Pac::CyrillicCodes.emplace(0xba, SpecialCharacter("P"));
	Pac::CyrillicCodes.emplace(0xbb, SpecialCharacter("Q"));
	Pac::CyrillicCodes.emplace(0xbc, SpecialCharacter("R"));
	Pac::CyrillicCodes.emplace(0xbd, SpecialCharacter("S"));
	Pac::CyrillicCodes.emplace(0xbe, SpecialCharacter("T"));
	Pac::CyrillicCodes.emplace(0xbf, SpecialCharacter("U"));
	Pac::CyrillicCodes.emplace(0xc0, SpecialCharacter("V"));
	Pac::CyrillicCodes.emplace(0xc1, SpecialCharacter("*"));
	Pac::CyrillicCodes.emplace(0xc2, SpecialCharacter("W"));
	Pac::CyrillicCodes.emplace(0xc3, SpecialCharacter("X"));
	Pac::CyrillicCodes.emplace(0xc4, SpecialCharacter("Y"));
	Pac::CyrillicCodes.emplace(0xc5, SpecialCharacter("Z"));
	Pac::CyrillicCodes.emplace(0xc6, SpecialCharacter("b"));
	Pac::CyrillicCodes.emplace(0xc7, SpecialCharacter("c"));
	Pac::CyrillicCodes.emplace(0xc8, SpecialCharacter("d"));
	Pac::CyrillicCodes.emplace(0xc9, SpecialCharacter("e"));
	Pac::CyrillicCodes.emplace(0xca, SpecialCharacter("f"));
	Pac::CyrillicCodes.emplace(0xcb, SpecialCharacter("g"));
	Pac::CyrillicCodes.emplace(0xcc, SpecialCharacter("h"));
	Pac::CyrillicCodes.emplace(0xcd, SpecialCharacter("i"));
	Pac::CyrillicCodes.emplace(0xce, SpecialCharacter("j"));
	Pac::CyrillicCodes.emplace(0xcf, SpecialCharacter("k"));
	Pac::CyrillicCodes.emplace(0xd0, SpecialCharacter("—"));
	Pac::CyrillicCodes.emplace(0xd1, SpecialCharacter("l"));
	Pac::CyrillicCodes.emplace(0xd2, SpecialCharacter("m"));
	Pac::CyrillicCodes.emplace(0xd3, SpecialCharacter("n"));
	Pac::CyrillicCodes.emplace(0xd4, SpecialCharacter("o"));
	Pac::CyrillicCodes.emplace(0xd5, SpecialCharacter("p"));
	Pac::CyrillicCodes.emplace(0xd6, SpecialCharacter("q"));
	Pac::CyrillicCodes.emplace(0xd7, SpecialCharacter("r"));
	Pac::CyrillicCodes.emplace(0xd8, SpecialCharacter("s"));
	Pac::CyrillicCodes.emplace(0xd9, SpecialCharacter("t"));
	Pac::CyrillicCodes.emplace(0xda, SpecialCharacter("u"));
	Pac::CyrillicCodes.emplace(0xdb, SpecialCharacter("v"));
	Pac::CyrillicCodes.emplace(0xdc, SpecialCharacter("w"));
	Pac::CyrillicCodes.emplace(0xdd, SpecialCharacter("э"));
	Pac::CyrillicCodes.emplace(0xde, SpecialCharacter("ю"));
	Pac::CyrillicCodes.emplace(0xdf, SpecialCharacter("z"));
	Pac::CyrillicCodes.emplace(0xe3, SpecialCharacter("`"));
	Pac::CyrillicCodes.emplace(0xe5, SpecialCharacter("¨"));
	Pac::CyrillicCodes.emplace(0xe020, SpecialCharacter("˘"));
	Pac::CyrillicCodes.emplace(0xe03a, SpecialCharacter("Ӂ"));
	Pac::CyrillicCodes.emplace(0xe03b, SpecialCharacter("ӂ"));
	Pac::CyrillicCodes.emplace(0xe042, SpecialCharacter("Й"));
	Pac::CyrillicCodes.emplace(0xe045, SpecialCharacter("Ў"));
	Pac::CyrillicCodes.emplace(0xe046, SpecialCharacter("Ӑ"));
	Pac::CyrillicCodes.emplace(0xe054, SpecialCharacter("Ӗ"));
	Pac::CyrillicCodes.emplace(0xe062, SpecialCharacter("й"));
	Pac::CyrillicCodes.emplace(0xe065, SpecialCharacter("ў"));
	Pac::CyrillicCodes.emplace(0xe066, SpecialCharacter("ӑ"));
	Pac::CyrillicCodes.emplace(0xe074, SpecialCharacter("ӗ"));
	Pac::CyrillicCodes.emplace(0xe220, SpecialCharacter("´"));
	Pac::CyrillicCodes.emplace(0xe252, SpecialCharacter("Ќ"));
	Pac::CyrillicCodes.emplace(0xe255, SpecialCharacter("Ѓ"));
	Pac::CyrillicCodes.emplace(0xe272, SpecialCharacter("ќ"));
	Pac::CyrillicCodes.emplace(0xe275, SpecialCharacter("ѓ"));
	Pac::CyrillicCodes.emplace(0xe342, SpecialCharacter("Ѝ"));
	Pac::CyrillicCodes.emplace(0xe354, SpecialCharacter("Ѐ"));
	Pac::CyrillicCodes.emplace(0xe362, SpecialCharacter("ѝ"));
	Pac::CyrillicCodes.emplace(0xe374, SpecialCharacter("ѐ"));
	Pac::CyrillicCodes.emplace(0xe522, SpecialCharacter("Ӭ"));
	Pac::CyrillicCodes.emplace(0xe527, SpecialCharacter("ӭ"));
}


void Pac::AddCyrillicCodes3()
{
	Pac::CyrillicCodes.emplace(0xe53a, SpecialCharacter("Ӝ"));
	Pac::CyrillicCodes.emplace(0xe53b, SpecialCharacter("ӝ"));
	Pac::CyrillicCodes.emplace(0xe542, SpecialCharacter("Ӥ"));
	Pac::CyrillicCodes.emplace(0xe545, SpecialCharacter("Ӱ"));
	Pac::CyrillicCodes.emplace(0xe546, SpecialCharacter("Ӓ"));
	Pac::CyrillicCodes.emplace(0xe54a, SpecialCharacter("Ӧ"));
	Pac::CyrillicCodes.emplace(0xe550, SpecialCharacter("Ӟ"));
	Pac::CyrillicCodes.emplace(0xe553, SpecialCharacter("Ӹ"));
	Pac::CyrillicCodes.emplace(0xe554, SpecialCharacter("Ё"));
	Pac::CyrillicCodes.emplace(0xe558, SpecialCharacter("Ӵ"));
	Pac::CyrillicCodes.emplace(0xe562, SpecialCharacter("ӥ"));
	Pac::CyrillicCodes.emplace(0xe565, SpecialCharacter("ӱ"));
	Pac::CyrillicCodes.emplace(0xe566, SpecialCharacter("ӓ"));
	Pac::CyrillicCodes.emplace(0xe56a, SpecialCharacter("ӧ"));
	Pac::CyrillicCodes.emplace(0xe570, SpecialCharacter("ӟ"));
	Pac::CyrillicCodes.emplace(0xe573, SpecialCharacter("ӹ"));
	Pac::CyrillicCodes.emplace(0xe574, SpecialCharacter("ё"));
	Pac::CyrillicCodes.emplace(0xe578, SpecialCharacter("ӵ"));
	Pac::CyrillicCodes.emplace(0xe586, SpecialCharacter("Ї"));
	Pac::CyrillicCodes.emplace(0xe596, SpecialCharacter("ї"));
	Pac::CyrillicCodes.emplace(0xe5b4, SpecialCharacter("Ї"));
}


void Pac::AddGreekCodes1()
{
	Pac::GreekCodes.emplace(0x20, SpecialCharacter(" "));
	Pac::GreekCodes.emplace(0x21, SpecialCharacter("!"));
	Pac::GreekCodes.emplace(0x22, SpecialCharacter("\""));
	Pac::GreekCodes.emplace(0x23, SpecialCharacter("£"));
	Pac::GreekCodes.emplace(0x24, SpecialCharacter("$"));
	Pac::GreekCodes.emplace(0x25, SpecialCharacter("%"));
	Pac::GreekCodes.emplace(0x26, SpecialCharacter("&"));
	Pac::GreekCodes.emplace(0x27, SpecialCharacter("'"));
	Pac::GreekCodes.emplace(0x28, SpecialCharacter("("));
	Pac::GreekCodes.emplace(0x29, SpecialCharacter(")"));
	Pac::GreekCodes.emplace(0x2A, SpecialCharacter("*"));
	Pac::GreekCodes.emplace(0x2B, SpecialCharacter("+"));
	Pac::GreekCodes.emplace(0x2C, SpecialCharacter(","));
	Pac::GreekCodes.emplace(0x2D, SpecialCharacter("-"));
	Pac::GreekCodes.emplace(0x2E, SpecialCharacter("."));
	Pac::GreekCodes.emplace(0x2F, SpecialCharacter("/"));
	Pac::GreekCodes.emplace(0x3A, SpecialCharacter(":"));
	Pac::GreekCodes.emplace(0x3B, SpecialCharacter(";"));
	Pac::GreekCodes.emplace(0x3C, SpecialCharacter("<"));
	Pac::GreekCodes.emplace(0x3D, SpecialCharacter("="));
	Pac::GreekCodes.emplace(0x3E, SpecialCharacter(">"));
	Pac::GreekCodes.emplace(0x3F, SpecialCharacter("?"));
	Pac::GreekCodes.emplace(0x40, SpecialCharacter("@"));
	Pac::GreekCodes.emplace(0x41, SpecialCharacter("Α"));
	Pac::GreekCodes.emplace(0x42, SpecialCharacter("Β"));
	Pac::GreekCodes.emplace(0x43, SpecialCharacter("Γ"));
	Pac::GreekCodes.emplace(0x44, SpecialCharacter("Δ"));
	Pac::GreekCodes.emplace(0x45, SpecialCharacter("Ε"));
	Pac::GreekCodes.emplace(0x46, SpecialCharacter("Ζ"));
	Pac::GreekCodes.emplace(0x47, SpecialCharacter("Η"));
	Pac::GreekCodes.emplace(0x48, SpecialCharacter("Θ"));
	Pac::GreekCodes.emplace(0x49, SpecialCharacter("Ι"));
	Pac::GreekCodes.emplace(0x4A, SpecialCharacter("Κ"));
	Pac::GreekCodes.emplace(0x4B, SpecialCharacter("Λ"));
	Pac::GreekCodes.emplace(0x4C, SpecialCharacter("Μ"));
	Pac::GreekCodes.emplace(0x4D, SpecialCharacter("Ν"));
	Pac::GreekCodes.emplace(0x4E, SpecialCharacter("Ξ"));
	Pac::GreekCodes.emplace(0x4F, SpecialCharacter("Ο"));
	Pac::GreekCodes.emplace(0x50, SpecialCharacter("Π"));
	Pac::GreekCodes.emplace(0x51, SpecialCharacter("Ρ"));
	Pac::GreekCodes.emplace(0x52, SpecialCharacter("R"));
	Pac::GreekCodes.emplace(0x53, SpecialCharacter("Σ"));
	Pac::GreekCodes.emplace(0x54, SpecialCharacter("Τ"));
	Pac::GreekCodes.emplace(0x55, SpecialCharacter("Υ"));
	Pac::GreekCodes.emplace(0x56, SpecialCharacter("Φ"));
	Pac::GreekCodes.emplace(0x57, SpecialCharacter("Χ"));
	Pac::GreekCodes.emplace(0x58, SpecialCharacter("Ψ"));
	Pac::GreekCodes.emplace(0x59, SpecialCharacter("Ω"));
	Pac::GreekCodes.emplace(0x5A, SpecialCharacter("Z"));

	Pac::GreekCodes.emplace(0x5F, SpecialCharacter("-"));

	Pac::GreekCodes.emplace(0x61, SpecialCharacter("α"));
	Pac::GreekCodes.emplace(0x62, SpecialCharacter("β"));
	Pac::GreekCodes.emplace(0x63, SpecialCharacter("γ"));
	Pac::GreekCodes.emplace(0x64, SpecialCharacter("δ"));
	Pac::GreekCodes.emplace(0x65, SpecialCharacter("ε"));
	Pac::GreekCodes.emplace(0x66, SpecialCharacter("ζ"));
	Pac::GreekCodes.emplace(0x67, SpecialCharacter("η"));
	Pac::GreekCodes.emplace(0x68, SpecialCharacter("θ"));
	Pac::GreekCodes.emplace(0x69, SpecialCharacter("ι"));
	Pac::GreekCodes.emplace(0x6A, SpecialCharacter("κ"));
	Pac::GreekCodes.emplace(0x6B, SpecialCharacter("λ"));
	Pac::GreekCodes.emplace(0x6C, SpecialCharacter("μ"));
	Pac::GreekCodes.emplace(0x6D, SpecialCharacter("ν"));
	Pac::GreekCodes.emplace(0x6E, SpecialCharacter("ξ"));
	Pac::GreekCodes.emplace(0x6F, SpecialCharacter("ο"));
	Pac::GreekCodes.emplace(0x70, SpecialCharacter("π"));
	Pac::GreekCodes.emplace(0x71, SpecialCharacter("ρ"));
	Pac::GreekCodes.emplace(0x72, SpecialCharacter("ς"));
	Pac::GreekCodes.emplace(0x73, SpecialCharacter("σ"));
	Pac::GreekCodes.emplace(0x74, SpecialCharacter("τ"));
	Pac::GreekCodes.emplace(0x75, SpecialCharacter("υ"));
	Pac::GreekCodes.emplace(0x76, SpecialCharacter("φ"));
	Pac::GreekCodes.emplace(0x77, SpecialCharacter("χ"));
	Pac::GreekCodes.emplace(0x78, SpecialCharacter("ψ"));
	Pac::GreekCodes.emplace(0x79, SpecialCharacter("ω"));
	Pac::GreekCodes.emplace(0x7A, SpecialCharacter("z"));
	Pac::GreekCodes.emplace(0x7E, SpecialCharacter("§"));
	Pac::GreekCodes.emplace(0x80, SpecialCharacter("#"));
	Pac::GreekCodes.emplace(0x81, SpecialCharacter("ß"));
	Pac::GreekCodes.emplace(0x82, SpecialCharacter("²"));
	Pac::GreekCodes.emplace(0x83, SpecialCharacter("³"));
	Pac::GreekCodes.emplace(0x84, SpecialCharacter("«"));
	Pac::GreekCodes.emplace(0x85, SpecialCharacter("»"));
}

void Pac::AddGreekCodes2()
{
	Pac::GreekCodes.emplace(0x86, SpecialCharacter("±"));
	Pac::GreekCodes.emplace(0x87, SpecialCharacter("þ"));
	Pac::GreekCodes.emplace(0x88, SpecialCharacter("Þ"));
	Pac::GreekCodes.emplace(0x89, SpecialCharacter("ð"));
	Pac::GreekCodes.emplace(0x8C, SpecialCharacter("A"));
	Pac::GreekCodes.emplace(0x8D, SpecialCharacter("B"));
	Pac::GreekCodes.emplace(0x8E, SpecialCharacter("C"));
	Pac::GreekCodes.emplace(0x8F, SpecialCharacter("D"));
	Pac::GreekCodes.emplace(0x90, SpecialCharacter("E"));
	Pac::GreekCodes.emplace(0x91, SpecialCharacter("F"));
	Pac::GreekCodes.emplace(0x92, SpecialCharacter("G"));
	Pac::GreekCodes.emplace(0x93, SpecialCharacter("H"));
	Pac::GreekCodes.emplace(0x94, SpecialCharacter("I"));
	Pac::GreekCodes.emplace(0x95, SpecialCharacter("J"));
	Pac::GreekCodes.emplace(0x96, SpecialCharacter("K"));
	Pac::GreekCodes.emplace(0x97, SpecialCharacter(""));
	Pac::GreekCodes.emplace(0x98, SpecialCharacter("M"));
	Pac::GreekCodes.emplace(0x99, SpecialCharacter("N"));
	Pac::GreekCodes.emplace(0x9A, SpecialCharacter("O"));
	Pac::GreekCodes.emplace(0x9B, SpecialCharacter("P"));
	Pac::GreekCodes.emplace(0x9C, SpecialCharacter("Q"));
	Pac::GreekCodes.emplace(0x9D, SpecialCharacter("R"));
	Pac::GreekCodes.emplace(0x9E, SpecialCharacter("S"));
	Pac::GreekCodes.emplace(0x9F, SpecialCharacter("T"));
	Pac::GreekCodes.emplace(0xA0, SpecialCharacter("U"));
	Pac::GreekCodes.emplace(0xA1, SpecialCharacter("V"));
	Pac::GreekCodes.emplace(0xA2, SpecialCharacter("W"));
	Pac::GreekCodes.emplace(0xA3, SpecialCharacter("X"));
	Pac::GreekCodes.emplace(0xA4, SpecialCharacter("Y"));
	Pac::GreekCodes.emplace(0xA5, SpecialCharacter("Z"));
	Pac::GreekCodes.emplace(0xA9, SpecialCharacter("°"));
	Pac::GreekCodes.emplace(0xAB, SpecialCharacter("½"));
	Pac::GreekCodes.emplace(0xAC, SpecialCharacter("a"));
	Pac::GreekCodes.emplace(0xAD, SpecialCharacter("b"));
	Pac::GreekCodes.emplace(0xAE, SpecialCharacter("c"));
	Pac::GreekCodes.emplace(0xAF, SpecialCharacter("d"));
	Pac::GreekCodes.emplace(0xB0, SpecialCharacter("e"));
	Pac::GreekCodes.emplace(0xB1, SpecialCharacter("f"));
	Pac::GreekCodes.emplace(0xB2, SpecialCharacter("g"));
	Pac::GreekCodes.emplace(0xB3, SpecialCharacter("h"));
	Pac::GreekCodes.emplace(0xB4, SpecialCharacter("i"));
	Pac::GreekCodes.emplace(0xB5, SpecialCharacter("j"));
	Pac::GreekCodes.emplace(0xB6, SpecialCharacter("k"));
	Pac::GreekCodes.emplace(0xB7, SpecialCharacter("l"));
	Pac::GreekCodes.emplace(0xB8, SpecialCharacter("m"));
	Pac::GreekCodes.emplace(0xB9, SpecialCharacter("n"));
	Pac::GreekCodes.emplace(0xBA, SpecialCharacter("o"));
	Pac::GreekCodes.emplace(0xBB, SpecialCharacter("p"));
	Pac::GreekCodes.emplace(0xBC, SpecialCharacter("q"));
	Pac::GreekCodes.emplace(0xBD, SpecialCharacter("r"));
	Pac::GreekCodes.emplace(0xBE, SpecialCharacter("s"));
	Pac::GreekCodes.emplace(0xBF, SpecialCharacter("t"));
	Pac::GreekCodes.emplace(0xC0, SpecialCharacter("u"));
	Pac::GreekCodes.emplace(0xC1, SpecialCharacter("v"));
	Pac::GreekCodes.emplace(0xC2, SpecialCharacter("w"));
	Pac::GreekCodes.emplace(0xC3, SpecialCharacter("x"));
	Pac::GreekCodes.emplace(0xC4, SpecialCharacter("y"));
	Pac::GreekCodes.emplace(0xC5, SpecialCharacter("z"));

	Pac::GreekCodes.emplace(0x202A, SpecialCharacter("®"));
	Pac::GreekCodes.emplace(0xE241, SpecialCharacter("Ά"));
	Pac::GreekCodes.emplace(0xE242, SpecialCharacter("Β́"));
	Pac::GreekCodes.emplace(0xE243, SpecialCharacter("Γ́"));
	Pac::GreekCodes.emplace(0xE244, SpecialCharacter("Δ́"));
	Pac::GreekCodes.emplace(0xE245, SpecialCharacter("Έ"));
	Pac::GreekCodes.emplace(0xE246, SpecialCharacter("Ζ́"));
	Pac::GreekCodes.emplace(0xE247, SpecialCharacter("Ή"));
	Pac::GreekCodes.emplace(0xE248, SpecialCharacter("Θ́"));
	Pac::GreekCodes.emplace(0xE249, SpecialCharacter("Ί"));
	Pac::GreekCodes.emplace(0xE24A, SpecialCharacter("Κ́"));
	Pac::GreekCodes.emplace(0xE24B, SpecialCharacter("Λ́"));
	Pac::GreekCodes.emplace(0xE24C, SpecialCharacter("Μ́"));
	Pac::GreekCodes.emplace(0xE24D, SpecialCharacter("Ν́"));
	Pac::GreekCodes.emplace(0xE24E, SpecialCharacter("Ξ́"));
	Pac::GreekCodes.emplace(0xE24F, SpecialCharacter("Ό"));
	Pac::GreekCodes.emplace(0xE255, SpecialCharacter("Ύ"));
	Pac::GreekCodes.emplace(0xE258, SpecialCharacter("Ψ́"));
	Pac::GreekCodes.emplace(0xE259, SpecialCharacter("Ώ"));
	Pac::GreekCodes.emplace(0xE261, SpecialCharacter("ά"));
	Pac::GreekCodes.emplace(0xE262, SpecialCharacter("β́"));
	Pac::GreekCodes.emplace(0xE263, SpecialCharacter("γ́"));
	Pac::GreekCodes.emplace(0xE264, SpecialCharacter("δ́"));
	Pac::GreekCodes.emplace(0xE265, SpecialCharacter("έ"));
	Pac::GreekCodes.emplace(0xE266, SpecialCharacter("ζ"));
	Pac::GreekCodes.emplace(0xE267, SpecialCharacter("ή"));
	Pac::GreekCodes.emplace(0xE268, SpecialCharacter("θ́"));
	Pac::GreekCodes.emplace(0xE269, SpecialCharacter("ί"));
	Pac::GreekCodes.emplace(0xE26A, SpecialCharacter("κ́"));
	Pac::GreekCodes.emplace(0xE26B, SpecialCharacter("λ́"));
	Pac::GreekCodes.emplace(0xE26C, SpecialCharacter("μ́"));
	Pac::GreekCodes.emplace(0xE26D, SpecialCharacter("ν́"));
	Pac::GreekCodes.emplace(0xE26E, SpecialCharacter("ξ"));
	Pac::GreekCodes.emplace(0xE26F, SpecialCharacter("ό"));
}
void Pac::AddGreekCodes3()
{
	Pac::GreekCodes.emplace(0xE270, SpecialCharacter("π"));
	Pac::GreekCodes.emplace(0xE271, SpecialCharacter("ρ́"));
	Pac::GreekCodes.emplace(0xE272, SpecialCharacter("ς́"));
	Pac::GreekCodes.emplace(0xE273, SpecialCharacter("σ́"));
	Pac::GreekCodes.emplace(0xE274, SpecialCharacter("τ́"));
	Pac::GreekCodes.emplace(0xE275, SpecialCharacter("ύ"));
	Pac::GreekCodes.emplace(0xE276, SpecialCharacter("φ́"));
	Pac::GreekCodes.emplace(0xE277, SpecialCharacter("χ́"));
	Pac::GreekCodes.emplace(0xE278, SpecialCharacter("ψ́"));
	Pac::GreekCodes.emplace(0xE279, SpecialCharacter("ώ"));
	Pac::GreekCodes.emplace(0xE27B, SpecialCharacter("ί"));
	Pac::GreekCodes.emplace(0xE320, SpecialCharacter("`"));
	Pac::GreekCodes.emplace(0xE399, SpecialCharacter("Ǹ"));
	Pac::GreekCodes.emplace(0xE39A, SpecialCharacter("Ò"));
	Pac::GreekCodes.emplace(0xE3A0, SpecialCharacter("Ù"));
	Pac::GreekCodes.emplace(0xE3A2, SpecialCharacter("Ẁ"));
	Pac::GreekCodes.emplace(0xE3A4, SpecialCharacter("Ỳ"));
	Pac::GreekCodes.emplace(0xE3B9, SpecialCharacter("ǹ"));
	Pac::GreekCodes.emplace(0xE3C2, SpecialCharacter("ẁ"));
	Pac::GreekCodes.emplace(0xE3C4, SpecialCharacter("ỳ"));
	Pac::GreekCodes.emplace(0xE549, SpecialCharacter("Ϊ"));
	Pac::GreekCodes.emplace(0xE555, SpecialCharacter("Ϋ"));
	Pac::GreekCodes.emplace(0xE561, SpecialCharacter("α̈"));
	Pac::GreekCodes.emplace(0xE562, SpecialCharacter("β̈"));
	Pac::GreekCodes.emplace(0xE563, SpecialCharacter("γ̈"));
	Pac::GreekCodes.emplace(0xE564, SpecialCharacter("δ̈"));
	Pac::GreekCodes.emplace(0xE565, SpecialCharacter("ε̈"));
	Pac::GreekCodes.emplace(0xE566, SpecialCharacter("ζ̈"));
	Pac::GreekCodes.emplace(0xE567, SpecialCharacter("η̈"));
	Pac::GreekCodes.emplace(0xE568, SpecialCharacter("θ̈"));
	Pac::GreekCodes.emplace(0xE569, SpecialCharacter("ϊ"));
	Pac::GreekCodes.emplace(0xE56A, SpecialCharacter("κ̈"));
	Pac::GreekCodes.emplace(0xE56B, SpecialCharacter("λ̈"));
	Pac::GreekCodes.emplace(0xE56C, SpecialCharacter("μ̈"));
	Pac::GreekCodes.emplace(0xE56D, SpecialCharacter("ν̈"));
	Pac::GreekCodes.emplace(0xE56E, SpecialCharacter("ξ̈"));
	Pac::GreekCodes.emplace(0xE56F, SpecialCharacter("ο̈"));
	Pac::GreekCodes.emplace(0xE570, SpecialCharacter("π̈"));
	Pac::GreekCodes.emplace(0xE571, SpecialCharacter("ρ"));
	Pac::GreekCodes.emplace(0xE572, SpecialCharacter("ς̈"));
	Pac::GreekCodes.emplace(0xE573, SpecialCharacter("σ̈"));
	Pac::GreekCodes.emplace(0xE574, SpecialCharacter("τ̈"));
	Pac::GreekCodes.emplace(0xE575, SpecialCharacter("ϋ"));
	Pac::GreekCodes.emplace(0xE576, SpecialCharacter("φ̈"));
	Pac::GreekCodes.emplace(0xE577, SpecialCharacter("χ̈"));
	Pac::GreekCodes.emplace(0xE578, SpecialCharacter("ψ̈"));
	Pac::GreekCodes.emplace(0xE579, SpecialCharacter("ω̈"));
	Pac::GreekCodes.emplace(0xE57B, SpecialCharacter("ϊ"));
	Pac::GreekCodes.emplace(0xE5E269, SpecialCharacter("ΐ"));
	Pac::GreekCodes.emplace(0xE5E275, SpecialCharacter("ΰ"));
}

void Pac::AddHebrewCode()
{
	Pac::HebrewCodes.emplace(0x80, SpecialCharacter("ְ"));
	Pac::HebrewCodes.emplace(0x81, SpecialCharacter("ֱ"));
	Pac::HebrewCodes.emplace(0x82, SpecialCharacter("ֲ"));
	Pac::HebrewCodes.emplace(0x83, SpecialCharacter("ֳ"));
	Pac::HebrewCodes.emplace(0x84, SpecialCharacter("ִ"));
	Pac::HebrewCodes.emplace(0x85, SpecialCharacter("ֵ"));
	Pac::HebrewCodes.emplace(0x86, SpecialCharacter("ֶ"));
	Pac::HebrewCodes.emplace(0x87, SpecialCharacter("ַ"));
	Pac::HebrewCodes.emplace(0x88, SpecialCharacter("ָ"));
	Pac::HebrewCodes.emplace(0x89, SpecialCharacter("ֹ"));
	Pac::HebrewCodes.emplace(0x8b, SpecialCharacter("ֻ"));
	Pac::HebrewCodes.emplace(0x8c, SpecialCharacter("ּ"));
	Pac::HebrewCodes.emplace(0x8d, SpecialCharacter("ֽ"));
	Pac::HebrewCodes.emplace(0x92, SpecialCharacter("֗"));
	Pac::HebrewCodes.emplace(0xa0, SpecialCharacter("א"));
	Pac::HebrewCodes.emplace(0xa1, SpecialCharacter("ב"));
	Pac::HebrewCodes.emplace(0xa2, SpecialCharacter("ג"));
	Pac::HebrewCodes.emplace(0xa3, SpecialCharacter("ד"));
	Pac::HebrewCodes.emplace(0xa4, SpecialCharacter("ה"));
	Pac::HebrewCodes.emplace(0xa5, SpecialCharacter("ו"));
	Pac::HebrewCodes.emplace(0xa6, SpecialCharacter("ז"));
	Pac::HebrewCodes.emplace(0xa7, SpecialCharacter("ח"));
	Pac::HebrewCodes.emplace(0xa8, SpecialCharacter("ט"));
	Pac::HebrewCodes.emplace(0xa9, SpecialCharacter("י"));
	Pac::HebrewCodes.emplace(0xaa, SpecialCharacter("ך"));
	Pac::HebrewCodes.emplace(0xab, SpecialCharacter("כ"));
	Pac::HebrewCodes.emplace(0xac, SpecialCharacter("ל"));
	Pac::HebrewCodes.emplace(0xad, SpecialCharacter("ם"));
	Pac::HebrewCodes.emplace(0xae, SpecialCharacter("מ"));
	Pac::HebrewCodes.emplace(0xaf, SpecialCharacter("ן"));
	Pac::HebrewCodes.emplace(0xb0, SpecialCharacter("נ"));
	Pac::HebrewCodes.emplace(0xb1, SpecialCharacter("ס"));
	Pac::HebrewCodes.emplace(0xb2, SpecialCharacter("ע"));
	Pac::HebrewCodes.emplace(0xb3, SpecialCharacter("ף"));
	Pac::HebrewCodes.emplace(0xb4, SpecialCharacter("פ"));
	Pac::HebrewCodes.emplace(0xb5, SpecialCharacter("ץ"));
	Pac::HebrewCodes.emplace(0xb6, SpecialCharacter("צ"));
	Pac::HebrewCodes.emplace(0xb7, SpecialCharacter("ק"));
	Pac::HebrewCodes.emplace(0xb8, SpecialCharacter("ר"));
	Pac::HebrewCodes.emplace(0xb9, SpecialCharacter("ש"));
	Pac::HebrewCodes.emplace(0xba, SpecialCharacter("ת"));
	Pac::HebrewCodes.emplace(0xbb, SpecialCharacter("װ"));
	Pac::HebrewCodes.emplace(0xbc, SpecialCharacter("ױ"));
	Pac::HebrewCodes.emplace(0xbd, SpecialCharacter("ײ"));
	Pac::HebrewCodes.emplace(0xcc, SpecialCharacter("ףּ"));
	Pac::HebrewCodes.emplace(0xcd, SpecialCharacter("רּ"));
	Pac::HebrewCodes.emplace(0xce, SpecialCharacter("אַ"));
	Pac::HebrewCodes.emplace(0xcf, SpecialCharacter("אּ"));
	Pac::HebrewCodes.emplace(0xd0, SpecialCharacter("אָ"));
	Pac::HebrewCodes.emplace(0xd1, SpecialCharacter("שּׂ"));
	Pac::HebrewCodes.emplace(0xd2, SpecialCharacter("שּׁ"));
	Pac::HebrewCodes.emplace(0xd3, SpecialCharacter("שׂ"));
	Pac::HebrewCodes.emplace(0xd4, SpecialCharacter("שׁ"));
	Pac::HebrewCodes.emplace(0xd5, SpecialCharacter("ﬥ"));
	Pac::HebrewCodes.emplace(0xd6, SpecialCharacter("ﬠ"));
	Pac::HebrewCodes.emplace(0xd7, SpecialCharacter("לּ"));
	Pac::HebrewCodes.emplace(0xd8, SpecialCharacter("יּ"));
	Pac::HebrewCodes.emplace(0xd9, SpecialCharacter("טּ"));
	Pac::HebrewCodes.emplace(0xda, SpecialCharacter("זּ"));
	Pac::HebrewCodes.emplace(0xdb, SpecialCharacter("וּ"));
	Pac::HebrewCodes.emplace(0xdc, SpecialCharacter("הּ"));
	Pac::HebrewCodes.emplace(0xdd, SpecialCharacter("דּ"));
	Pac::HebrewCodes.emplace(0xde, SpecialCharacter("גּ"));
	Pac::HebrewCodes.emplace(0xdf, SpecialCharacter("בּ"));
	Pac::HebrewCodes.emplace(0x2b, SpecialCharacter("."));
	Pac::HebrewCodes.emplace(0x2c, SpecialCharacter(","));
}



void Pac::AddLatinCodes1()
{
	Pac::LatinCodes.emplace(0xe041, SpecialCharacter("Ã"));
	Pac::LatinCodes.emplace(0xe04e, SpecialCharacter("Ñ"));
	Pac::LatinCodes.emplace(0xe04f, SpecialCharacter("Õ"));
	Pac::LatinCodes.emplace(0xe061, SpecialCharacter("ã"));
	Pac::LatinCodes.emplace(0xe06e, SpecialCharacter("ñ"));
	Pac::LatinCodes.emplace(0xe06f, SpecialCharacter("õ"));
	Pac::LatinCodes.emplace(0xe161, SpecialCharacter("å"));
	Pac::LatinCodes.emplace(0xe141, SpecialCharacter("Å"));

	Pac::LatinCodes.emplace(0x618a, SpecialCharacter("ā"));
	Pac::LatinCodes.emplace(0x418a, SpecialCharacter("Ā"));
	Pac::LatinCodes.emplace(0x458a, SpecialCharacter("Ē"));
	Pac::LatinCodes.emplace(0x658a, SpecialCharacter("ē"));
	Pac::LatinCodes.emplace(0x498a, SpecialCharacter("Ī"));
	Pac::LatinCodes.emplace(0x698a, SpecialCharacter("ī"));
	Pac::LatinCodes.emplace(0x4f8a, SpecialCharacter("Ō"));
	Pac::LatinCodes.emplace(0x6f8a, SpecialCharacter("ō"));
	Pac::LatinCodes.emplace(0x558a, SpecialCharacter("Ū"));
	Pac::LatinCodes.emplace(0x758a, SpecialCharacter("ū"));

	Pac::LatinCodes.emplace(0x23, SpecialCharacter("£"));
	Pac::LatinCodes.emplace(0x7c, SpecialCharacter("æ"));
	Pac::LatinCodes.emplace(0x7d, SpecialCharacter("ø"));
	Pac::LatinCodes.emplace(0x7e, SpecialCharacter("§"));
	Pac::LatinCodes.emplace(0x80, SpecialCharacter("#"));
	Pac::LatinCodes.emplace(0x5c, SpecialCharacter("Æ"));
	Pac::LatinCodes.emplace(0x5d, SpecialCharacter("Ø"));
	Pac::LatinCodes.emplace(0x5e, SpecialCharacter("÷"));
	Pac::LatinCodes.emplace(0x2d, SpecialCharacter("-"));
	Pac::LatinCodes.emplace(0x5f, SpecialCharacter("–"));
	Pac::LatinCodes.emplace(0xE54f, SpecialCharacter("Ö"));
	Pac::LatinCodes.emplace(0xE56f, SpecialCharacter("ö"));
	Pac::LatinCodes.emplace(0xe541, SpecialCharacter("Ä"));
	Pac::LatinCodes.emplace(0xe561, SpecialCharacter("ä"));
	Pac::LatinCodes.emplace(0xe555, SpecialCharacter("Ü"));
	Pac::LatinCodes.emplace(0xe575, SpecialCharacter("ü"));
	Pac::LatinCodes.emplace(0x81, SpecialCharacter("ß"));
	Pac::LatinCodes.emplace(0x82, SpecialCharacter("²"));
	Pac::LatinCodes.emplace(0xe241, SpecialCharacter("Á"));
	Pac::LatinCodes.emplace(0xe249, SpecialCharacter("Í"));
	Pac::LatinCodes.emplace(0xe255, SpecialCharacter("Ú"));
	Pac::LatinCodes.emplace(0xe259, SpecialCharacter("Ý"));
	Pac::LatinCodes.emplace(0xe261, SpecialCharacter("á"));
	Pac::LatinCodes.emplace(0xe265, SpecialCharacter("é"));
	Pac::LatinCodes.emplace(0xe269, SpecialCharacter("í"));
	Pac::LatinCodes.emplace(0xe245, SpecialCharacter("É"));
	Pac::LatinCodes.emplace(0xe275, SpecialCharacter("ú")); // or "ѓ" !?
	Pac::LatinCodes.emplace(0xe279, SpecialCharacter("ý"));
	Pac::LatinCodes.emplace(0xe361, SpecialCharacter("à"));
	Pac::LatinCodes.emplace(0xe365, SpecialCharacter("è"));
	Pac::LatinCodes.emplace(0xe36f, SpecialCharacter("ò"));
	Pac::LatinCodes.emplace(0xe345, SpecialCharacter("È"));
	Pac::LatinCodes.emplace(0xe349, SpecialCharacter("Ì"));
	Pac::LatinCodes.emplace(0xe34f, SpecialCharacter("Ò"));
	Pac::LatinCodes.emplace(0xe369, SpecialCharacter("ì"));

	Pac::LatinCodes.emplace(0xe443, SpecialCharacter("Ĉ"));
	Pac::LatinCodes.emplace(0xe447, SpecialCharacter("Ĝ"));
	Pac::LatinCodes.emplace(0xe448, SpecialCharacter("Ĥ"));
	Pac::LatinCodes.emplace(0xe44A, SpecialCharacter("Ĵ"));
	Pac::LatinCodes.emplace(0xe453, SpecialCharacter("Ŝ"));
	Pac::LatinCodes.emplace(0xeA55, SpecialCharacter("Ǔ"));
	Pac::LatinCodes.emplace(0xe463, SpecialCharacter("ĉ"));
	Pac::LatinCodes.emplace(0xe467, SpecialCharacter("ĝ"));
	Pac::LatinCodes.emplace(0xe468, SpecialCharacter("ĥ"));
	Pac::LatinCodes.emplace(0xe46A, SpecialCharacter("ĵ"));
	Pac::LatinCodes.emplace(0xe473, SpecialCharacter("ŝ"));
	Pac::LatinCodes.emplace(0xeA75, SpecialCharacter("ǔ"));
	Pac::LatinCodes.emplace(0xe341, SpecialCharacter("À"));
	Pac::LatinCodes.emplace(0xe441, SpecialCharacter("Â"));
	Pac::LatinCodes.emplace(0xe461, SpecialCharacter("â"));
	Pac::LatinCodes.emplace(0xe643, SpecialCharacter("Ç"));
	Pac::LatinCodes.emplace(0xe663, SpecialCharacter("ç"));
	Pac::LatinCodes.emplace(0xe445, SpecialCharacter("Ê"));
	Pac::LatinCodes.emplace(0xe465, SpecialCharacter("ê"));
	Pac::LatinCodes.emplace(0xe545, SpecialCharacter("Ë"));
	Pac::LatinCodes.emplace(0xe565, SpecialCharacter("ë"));
	Pac::LatinCodes.emplace(0xe449, SpecialCharacter("Î"));
	Pac::LatinCodes.emplace(0xe469, SpecialCharacter("î"));
	Pac::LatinCodes.emplace(0xe549, SpecialCharacter("Ï"));
	Pac::LatinCodes.emplace(0xe569, SpecialCharacter("ï"));
	Pac::LatinCodes.emplace(0xe44F, SpecialCharacter("Ô"));
	Pac::LatinCodes.emplace(0xe46F, SpecialCharacter("ô"));
	Pac::LatinCodes.emplace(0xe355, SpecialCharacter("Ù"));
	Pac::LatinCodes.emplace(0xe375, SpecialCharacter("ù"));
	Pac::LatinCodes.emplace(0xe455, SpecialCharacter("Û"));
	Pac::LatinCodes.emplace(0xe475, SpecialCharacter("û"));
	Pac::LatinCodes.emplace(0xe559, SpecialCharacter("Ÿ"));
	Pac::LatinCodes.emplace(0xe579, SpecialCharacter("ÿ"));
	Pac::LatinCodes.emplace(0xeb41, SpecialCharacter("Ą"));
}



void Pac::AddLatinCodes2()
{
	Pac::LatinCodes.emplace(0xeb61, SpecialCharacter("ą"));
	Pac::LatinCodes.emplace(0xe243, SpecialCharacter("Ć"));
	Pac::LatinCodes.emplace(0xe263, SpecialCharacter("ć"));
	Pac::LatinCodes.emplace(0xeB45, SpecialCharacter("Ę"));
	Pac::LatinCodes.emplace(0xeB65, SpecialCharacter("ę"));
	Pac::LatinCodes.emplace(0x9c, SpecialCharacter("Ł"));
	Pac::LatinCodes.emplace(0xbc, SpecialCharacter("ł"));
	Pac::LatinCodes.emplace(0xe24e, SpecialCharacter("Ń"));
	Pac::LatinCodes.emplace(0xe26e, SpecialCharacter("ń"));
	Pac::LatinCodes.emplace(0xe24f, SpecialCharacter("Ó"));
	Pac::LatinCodes.emplace(0xe26f, SpecialCharacter("ó"));
	Pac::LatinCodes.emplace(0xe253, SpecialCharacter("Ś"));
	Pac::LatinCodes.emplace(0xe273, SpecialCharacter("ś"));
	Pac::LatinCodes.emplace(0xe25a, SpecialCharacter("Ź"));
	Pac::LatinCodes.emplace(0xe27a, SpecialCharacter("ź"));
	Pac::LatinCodes.emplace(0xe85a, SpecialCharacter("Ż"));
	Pac::LatinCodes.emplace(0xe87a, SpecialCharacter("ż"));
	Pac::LatinCodes.emplace(0x87, SpecialCharacter("þ"));
	Pac::LatinCodes.emplace(0x89, SpecialCharacter("ð"));
	Pac::LatinCodes.emplace(0x88, SpecialCharacter("Þ"));
	Pac::LatinCodes.emplace(0x8c, SpecialCharacter("Đ"));

	Pac::LatinCodes.emplace(0xe653, SpecialCharacter("Ş"));
	Pac::LatinCodes.emplace(0xe673, SpecialCharacter("ş"));
	Pac::LatinCodes.emplace(0x7b, SpecialCharacter("ı"));
	Pac::LatinCodes.emplace(0xeA67, SpecialCharacter("ǧ"));
	Pac::LatinCodes.emplace(0xeA47, SpecialCharacter("Ǧ"));
	Pac::LatinCodes.emplace(0xe849, SpecialCharacter("İ"));

	Pac::LatinCodes.emplace(0xE75A, SpecialCharacter("Ž"));
	Pac::LatinCodes.emplace(0xE753, SpecialCharacter("Š"));
	Pac::LatinCodes.emplace(0xE743, SpecialCharacter("Č"));

	Pac::LatinCodes.emplace(0xE77A, SpecialCharacter("ž"));
	Pac::LatinCodes.emplace(0xE773, SpecialCharacter("š"));
	Pac::LatinCodes.emplace(0xE763, SpecialCharacter("č"));
	Pac::LatinCodes.emplace(0xAE, SpecialCharacter("đ"));

	Pac::LatinCodes.emplace(0xA8, SpecialCharacter("¿"));
	Pac::LatinCodes.emplace(0xAD, SpecialCharacter("¡"));
	Pac::LatinCodes.emplace(0xA6, SpecialCharacter("ª"));
	Pac::LatinCodes.emplace(0xA7, SpecialCharacter("º"));

	Pac::LatinCodes.emplace(0xAB, SpecialCharacter("½"));
	Pac::LatinCodes.emplace(0xBB, SpecialCharacter("»"));
	Pac::LatinCodes.emplace(0xB3, SpecialCharacter("³"));
	Pac::LatinCodes.emplace(0x1C, SpecialCharacter("“"));
	Pac::LatinCodes.emplace(0x1D, SpecialCharacter("”"));
	Pac::LatinCodes.emplace(0x18, SpecialCharacter("‘"));
	Pac::LatinCodes.emplace(0x19, SpecialCharacter("’"));
	Pac::LatinCodes.emplace(0x13, SpecialCharacter("–"));
	Pac::LatinCodes.emplace(0x14, SpecialCharacter("—"));
	Pac::LatinCodes.emplace(0x83, SpecialCharacter("³"));
	Pac::LatinCodes.emplace(0x5B, SpecialCharacter("¤"));
	Pac::LatinCodes.emplace(0x85, SpecialCharacter("ŧ"));
	Pac::LatinCodes.emplace(0x86, SpecialCharacter("Ŧ"));
	Pac::LatinCodes.emplace(0x8A, SpecialCharacter("«"));
	Pac::LatinCodes.emplace(0x8B, SpecialCharacter("»"));
	Pac::LatinCodes.emplace(0x8E, SpecialCharacter("Ŋ"));
	Pac::LatinCodes.emplace(0x8D, SpecialCharacter("ŋ"));
	Pac::LatinCodes.emplace(0x95, SpecialCharacter("Ħ"));
	Pac::LatinCodes.emplace(0x96, SpecialCharacter("ħ"));
	Pac::LatinCodes.emplace(0x9A, SpecialCharacter("Œ"));
	Pac::LatinCodes.emplace(0x9B, SpecialCharacter("¢"));
	Pac::LatinCodes.emplace(0x9D, SpecialCharacter("¥"));
	Pac::LatinCodes.emplace(0x9E, SpecialCharacter("€"));
	Pac::LatinCodes.emplace(0xA9, SpecialCharacter("°"));
	Pac::LatinCodes.emplace(0xAA, SpecialCharacter("¾"));
	Pac::LatinCodes.emplace(0xAC, SpecialCharacter("¼"));
	Pac::LatinCodes.emplace(0xB1, SpecialCharacter("±"));
	Pac::LatinCodes.emplace(0xB5, SpecialCharacter("µ"));
	Pac::LatinCodes.emplace(0xBA, SpecialCharacter("œ"));
	Pac::LatinCodes.emplace(0xBF, SpecialCharacter("ǧ"));
	Pac::LatinCodes.emplace(0xD2, SpecialCharacter("®"));
	Pac::LatinCodes.emplace(0xD4, SpecialCharacter("©"));
	Pac::LatinCodes.emplace(0x4CE2, SpecialCharacter("Ľ", false, 1));
	Pac::LatinCodes.emplace(0x74E2, SpecialCharacter("ť", false, 1));
	Pac::LatinCodes.emplace(0x64E2, SpecialCharacter("ď", false, 1));
	Pac::LatinCodes.emplace(0x6CE2, SpecialCharacter("ľ", false, 1));
	Pac::LatinCodes.emplace(0xE020, SpecialCharacter("˜", false, 0));
	Pac::LatinCodes.emplace(0xE045, SpecialCharacter("Ẽ"));
	Pac::LatinCodes.emplace(0xE049, SpecialCharacter("Ĩ"));
	Pac::LatinCodes.emplace(0xE055, SpecialCharacter("Ũ"));
	Pac::LatinCodes.emplace(0xE056, SpecialCharacter("Ṽ"));
	Pac::LatinCodes.emplace(0xE059, SpecialCharacter("Ỹ"));
	Pac::LatinCodes.emplace(0xE065, SpecialCharacter("ẽ"));
	Pac::LatinCodes.emplace(0xE069, SpecialCharacter("ĩ"));
	Pac::LatinCodes.emplace(0xE075, SpecialCharacter("ũ"));
	Pac::LatinCodes.emplace(0xE076, SpecialCharacter("ṽ"));
	Pac::LatinCodes.emplace(0xE079, SpecialCharacter("ỹ"));
	Pac::LatinCodes.emplace(0xE120, SpecialCharacter("˚", false, 0));
	Pac::LatinCodes.emplace(0xE155, SpecialCharacter("Ů"));
	Pac::LatinCodes.emplace(0xE175, SpecialCharacter("ů"));
	Pac::LatinCodes.emplace(0xE177, SpecialCharacter("ẘ"));
}

void Pac::AddLatinCodes3()
{
	Pac::LatinCodes.emplace(0xE179, SpecialCharacter("ẙ"));
	Pac::LatinCodes.emplace(0xE220, SpecialCharacter("´", false, 0));
	Pac::LatinCodes.emplace(0xE247, SpecialCharacter("Ǵ"));
	Pac::LatinCodes.emplace(0xE24B, SpecialCharacter("Ḱ"));
	Pac::LatinCodes.emplace(0xE24C, SpecialCharacter("Ĺ"));
	Pac::LatinCodes.emplace(0xE24D, SpecialCharacter("Ḿ"));
	Pac::LatinCodes.emplace(0xE250, SpecialCharacter("Ṕ"));
	Pac::LatinCodes.emplace(0xE252, SpecialCharacter("Ŕ"));
	Pac::LatinCodes.emplace(0xE257, SpecialCharacter("Ẃ"));
	Pac::LatinCodes.emplace(0xE25C, SpecialCharacter("Ǽ"));
	Pac::LatinCodes.emplace(0xE25D, SpecialCharacter("Ǿ"));
	Pac::LatinCodes.emplace(0xE267, SpecialCharacter("ǵ"));
	Pac::LatinCodes.emplace(0xE26B, SpecialCharacter("ḱ"));
	Pac::LatinCodes.emplace(0xE26C, SpecialCharacter("ĺ"));
	Pac::LatinCodes.emplace(0xE26D, SpecialCharacter("ḿ"));
	Pac::LatinCodes.emplace(0xE270, SpecialCharacter("ṕ"));
	Pac::LatinCodes.emplace(0xE272, SpecialCharacter("ŕ"));
	Pac::LatinCodes.emplace(0xE277, SpecialCharacter("ẃ"));
	Pac::LatinCodes.emplace(0xE27C, SpecialCharacter("ǽ"));
	Pac::LatinCodes.emplace(0xE27D, SpecialCharacter("ǿ"));
	Pac::LatinCodes.emplace(0xE320, SpecialCharacter("`", false, 0));
	Pac::LatinCodes.emplace(0xE34E, SpecialCharacter("Ǹ"));
	Pac::LatinCodes.emplace(0xE357, SpecialCharacter("Ẁ"));
	Pac::LatinCodes.emplace(0xE359, SpecialCharacter("Ỳ"));
	Pac::LatinCodes.emplace(0xE36E, SpecialCharacter("ǹ"));
	Pac::LatinCodes.emplace(0xE377, SpecialCharacter("ẁ"));
	Pac::LatinCodes.emplace(0xE379, SpecialCharacter("ỳ"));
	Pac::LatinCodes.emplace(0xE420, SpecialCharacter("^", false, 0));
	Pac::LatinCodes.emplace(0xE457, SpecialCharacter("Ŵ"));
	Pac::LatinCodes.emplace(0xE459, SpecialCharacter("Ŷ"));
	Pac::LatinCodes.emplace(0xE45A, SpecialCharacter("Ẑ"));
	Pac::LatinCodes.emplace(0xE477, SpecialCharacter("ŵ"));
	Pac::LatinCodes.emplace(0xE479, SpecialCharacter("ŷ"));
	Pac::LatinCodes.emplace(0xE47A, SpecialCharacter("ẑ"));
	Pac::LatinCodes.emplace(0xE520, SpecialCharacter("¨", false, 0));
	Pac::LatinCodes.emplace(0xE548, SpecialCharacter("Ḧ"));
	Pac::LatinCodes.emplace(0xE557, SpecialCharacter("Ẅ"));
	Pac::LatinCodes.emplace(0xE558, SpecialCharacter("Ẍ"));
	Pac::LatinCodes.emplace(0xE568, SpecialCharacter("ḧ"));
	Pac::LatinCodes.emplace(0xE574, SpecialCharacter("ẗ"));
	Pac::LatinCodes.emplace(0xE577, SpecialCharacter("ẅ"));
	Pac::LatinCodes.emplace(0xE578, SpecialCharacter("ẍ"));
	Pac::LatinCodes.emplace(0xE620, SpecialCharacter("¸", false, 0));
	Pac::LatinCodes.emplace(0xE644, SpecialCharacter("Ḑ"));
	Pac::LatinCodes.emplace(0xE645, SpecialCharacter("Ȩ"));
	Pac::LatinCodes.emplace(0xE647, SpecialCharacter("Ģ"));
	Pac::LatinCodes.emplace(0xE648, SpecialCharacter("Ḩ"));
	Pac::LatinCodes.emplace(0xE64B, SpecialCharacter("Ķ"));
	Pac::LatinCodes.emplace(0xE64C, SpecialCharacter("Ļ"));
	Pac::LatinCodes.emplace(0xE64E, SpecialCharacter("Ņ"));
	Pac::LatinCodes.emplace(0xE652, SpecialCharacter("Ŗ"));
	Pac::LatinCodes.emplace(0xE654, SpecialCharacter("Ţ"));
	Pac::LatinCodes.emplace(0xE664, SpecialCharacter("ḑ"));
	Pac::LatinCodes.emplace(0xE665, SpecialCharacter("ȩ"));
	Pac::LatinCodes.emplace(0xE667, SpecialCharacter("ģ"));
	Pac::LatinCodes.emplace(0xE668, SpecialCharacter("ḩ"));
	Pac::LatinCodes.emplace(0xE66B, SpecialCharacter("ķ"));
	Pac::LatinCodes.emplace(0xE66C, SpecialCharacter("ļ"));
	Pac::LatinCodes.emplace(0xE66E, SpecialCharacter("ņ"));
	Pac::LatinCodes.emplace(0xE672, SpecialCharacter("ŗ"));
	Pac::LatinCodes.emplace(0xE674, SpecialCharacter("ţ"));
	Pac::LatinCodes.emplace(0xE720, SpecialCharacter("ˇ", false, 0));
	Pac::LatinCodes.emplace(0xE741, SpecialCharacter("Ă"));
	Pac::LatinCodes.emplace(0xE744, SpecialCharacter("Ď"));
	Pac::LatinCodes.emplace(0xE745, SpecialCharacter("Ě"));
	Pac::LatinCodes.emplace(0xE747, SpecialCharacter("Ǧ"));
	Pac::LatinCodes.emplace(0xE748, SpecialCharacter("Ȟ"));
	Pac::LatinCodes.emplace(0xE749, SpecialCharacter("Ǐ"));
	Pac::LatinCodes.emplace(0xE74B, SpecialCharacter("Ǩ"));
	Pac::LatinCodes.emplace(0xE74E, SpecialCharacter("Ň"));
	Pac::LatinCodes.emplace(0xE74F, SpecialCharacter("Ǒ"));
	Pac::LatinCodes.emplace(0xE752, SpecialCharacter("Ř"));
	Pac::LatinCodes.emplace(0xE754, SpecialCharacter("Ť"));
	Pac::LatinCodes.emplace(0xE755, SpecialCharacter("Ǔ"));
	Pac::LatinCodes.emplace(0xE761, SpecialCharacter("ă"));
	Pac::LatinCodes.emplace(0xE765, SpecialCharacter("ě"));
	Pac::LatinCodes.emplace(0xE768, SpecialCharacter("ȟ"));
	Pac::LatinCodes.emplace(0xE769, SpecialCharacter("ǐ"));
	Pac::LatinCodes.emplace(0xE76A, SpecialCharacter("ǰ"));
	Pac::LatinCodes.emplace(0xE76B, SpecialCharacter("ǩ"));
	Pac::LatinCodes.emplace(0xE76E, SpecialCharacter("ň"));
	Pac::LatinCodes.emplace(0xE76F, SpecialCharacter("ǒ"));
	Pac::LatinCodes.emplace(0xE772, SpecialCharacter("ř"));
	Pac::LatinCodes.emplace(0xE775, SpecialCharacter("ǔ"));
	Pac::LatinCodes.emplace(0xE820, SpecialCharacter("˙", false, 0));
}


void Pac::AddLatinCodes4()
{
	Pac::LatinCodes.emplace(0xE841, SpecialCharacter("Ȧ"));
	Pac::LatinCodes.emplace(0xE842, SpecialCharacter("Ḃ"));
	Pac::LatinCodes.emplace(0xE843, SpecialCharacter("Ċ"));
	Pac::LatinCodes.emplace(0xE844, SpecialCharacter("Ḋ"));
	Pac::LatinCodes.emplace(0xE845, SpecialCharacter("Ė"));
	Pac::LatinCodes.emplace(0xE846, SpecialCharacter("Ḟ"));
	Pac::LatinCodes.emplace(0xE847, SpecialCharacter("Ġ"));
	Pac::LatinCodes.emplace(0xE848, SpecialCharacter("Ḣ"));
	Pac::LatinCodes.emplace(0xE84D, SpecialCharacter("Ṁ"));
	Pac::LatinCodes.emplace(0xE84E, SpecialCharacter("Ṅ"));
	Pac::LatinCodes.emplace(0xE84F, SpecialCharacter("Ȯ"));
	Pac::LatinCodes.emplace(0xE850, SpecialCharacter("Ṗ"));
	Pac::LatinCodes.emplace(0xE852, SpecialCharacter("Ṙ"));
	Pac::LatinCodes.emplace(0xE853, SpecialCharacter("Ṡ"));
	Pac::LatinCodes.emplace(0xE854, SpecialCharacter("Ṫ"));
	Pac::LatinCodes.emplace(0xE857, SpecialCharacter("Ẇ"));
	Pac::LatinCodes.emplace(0xE858, SpecialCharacter("Ẋ"));
	Pac::LatinCodes.emplace(0xE859, SpecialCharacter("Ẏ"));
	Pac::LatinCodes.emplace(0xE861, SpecialCharacter("ȧ"));
	Pac::LatinCodes.emplace(0xE862, SpecialCharacter("ḃ"));
	Pac::LatinCodes.emplace(0xE863, SpecialCharacter("ċ"));
	Pac::LatinCodes.emplace(0xE864, SpecialCharacter("ḋ"));
	Pac::LatinCodes.emplace(0xE865, SpecialCharacter("ė"));
	Pac::LatinCodes.emplace(0xE866, SpecialCharacter("ḟ"));
	Pac::LatinCodes.emplace(0xE867, SpecialCharacter("ġ"));
	Pac::LatinCodes.emplace(0xE868, SpecialCharacter("ḣ"));
	Pac::LatinCodes.emplace(0xE86D, SpecialCharacter("ṁ"));
	Pac::LatinCodes.emplace(0xE86E, SpecialCharacter("ṅ"));
	Pac::LatinCodes.emplace(0xE86F, SpecialCharacter("ȯ"));
	Pac::LatinCodes.emplace(0xE870, SpecialCharacter("ṗ"));
	Pac::LatinCodes.emplace(0xE872, SpecialCharacter("ṙ"));
	Pac::LatinCodes.emplace(0xE873, SpecialCharacter("ṡ"));
	Pac::LatinCodes.emplace(0xE874, SpecialCharacter("ṫ"));
	Pac::LatinCodes.emplace(0xE877, SpecialCharacter("ẇ"));
	Pac::LatinCodes.emplace(0xE878, SpecialCharacter("ẋ"));
	Pac::LatinCodes.emplace(0xE879, SpecialCharacter("ẏ"));
	Pac::LatinCodes.emplace(0xE920, SpecialCharacter("¯", false, 0));
	Pac::LatinCodes.emplace(0xE941, SpecialCharacter("Ā"));
	Pac::LatinCodes.emplace(0xE945, SpecialCharacter("Ē"));
	Pac::LatinCodes.emplace(0xE947, SpecialCharacter("Ḡ"));
	Pac::LatinCodes.emplace(0xE949, SpecialCharacter("Ī"));
	Pac::LatinCodes.emplace(0xE94F, SpecialCharacter("Ō"));
	Pac::LatinCodes.emplace(0xE955, SpecialCharacter("Ū"));
	Pac::LatinCodes.emplace(0xE959, SpecialCharacter("Ȳ"));
	Pac::LatinCodes.emplace(0xE95C, SpecialCharacter("Ǣ"));
	Pac::LatinCodes.emplace(0xE961, SpecialCharacter("ā"));
	Pac::LatinCodes.emplace(0xE965, SpecialCharacter("ē"));
	Pac::LatinCodes.emplace(0xE967, SpecialCharacter("ḡ"));
	Pac::LatinCodes.emplace(0xE969, SpecialCharacter("ī"));
	Pac::LatinCodes.emplace(0xE96F, SpecialCharacter("ō"));
	Pac::LatinCodes.emplace(0xE975, SpecialCharacter("ū"));
	Pac::LatinCodes.emplace(0xE979, SpecialCharacter("ȳ"));
	Pac::LatinCodes.emplace(0xE97C, SpecialCharacter("ǣ"));
	Pac::LatinCodes.emplace(0xEA20, SpecialCharacter("ˇ", false, 0));
	Pac::LatinCodes.emplace(0xEA41, SpecialCharacter("Ă"));
	Pac::LatinCodes.emplace(0xEA45, SpecialCharacter("Ě"));
	Pac::LatinCodes.emplace(0xEA49, SpecialCharacter("Ǐ"));
	Pac::LatinCodes.emplace(0xEA4F, SpecialCharacter("Ǒ"));
	Pac::LatinCodes.emplace(0xEA61, SpecialCharacter("ă"));
	Pac::LatinCodes.emplace(0xEA65, SpecialCharacter("ě"));
	Pac::LatinCodes.emplace(0xEA69, SpecialCharacter("ǐ"));
	Pac::LatinCodes.emplace(0xEA6F, SpecialCharacter("ǒ"));
	Pac::LatinCodes.emplace(0xEB20, SpecialCharacter("˛", false, 0));
	Pac::LatinCodes.emplace(0xEB49, SpecialCharacter("Į"));
	Pac::LatinCodes.emplace(0xEB4F, SpecialCharacter("Ǫ"));
	Pac::LatinCodes.emplace(0xEB55, SpecialCharacter("Ų"));
	Pac::LatinCodes.emplace(0xEB69, SpecialCharacter("į"));
	Pac::LatinCodes.emplace(0xEB6F, SpecialCharacter("ǫ"));
	Pac::LatinCodes.emplace(0xEB75, SpecialCharacter("ų"));
	Pac::LatinCodes.emplace(0xEC20, SpecialCharacter("˝", false, 0));
	Pac::LatinCodes.emplace(0xEC4F, SpecialCharacter("Ő"));
	Pac::LatinCodes.emplace(0xEC55, SpecialCharacter("Ű"));
	Pac::LatinCodes.emplace(0xEC6F, SpecialCharacter("ő"));
	Pac::LatinCodes.emplace(0xEC75, SpecialCharacter("ű"));
}
void Pac::AddTurkishLatinCodes()
{
	Pac::LatinTurkishOverrides.emplace(0xE720, SpecialCharacter("˘", false, 0));
	Pac::LatinTurkishOverrides.emplace(0xE741, SpecialCharacter("Ă"));
	Pac::LatinTurkishOverrides.emplace(0xE745, SpecialCharacter("Ĕ"));
	Pac::LatinTurkishOverrides.emplace(0xE747, SpecialCharacter("Ğ"));
	Pac::LatinTurkishOverrides.emplace(0xE749, SpecialCharacter("Ĭ"));
	Pac::LatinTurkishOverrides.emplace(0xE74F, SpecialCharacter("Ŏ"));
	Pac::LatinTurkishOverrides.emplace(0xE755, SpecialCharacter("Ŭ"));
	Pac::LatinTurkishOverrides.emplace(0xE761, SpecialCharacter("ă"));
	Pac::LatinTurkishOverrides.emplace(0xE765, SpecialCharacter("ĕ"));
	Pac::LatinTurkishOverrides.emplace(0xE769, SpecialCharacter("ĭ"));
	Pac::LatinTurkishOverrides.emplace(0xE76F, SpecialCharacter("ŏ"));
	Pac::LatinTurkishOverrides.emplace(0xE775, SpecialCharacter("ŭ"));

	Pac::LatinTurkishOverrides.emplace(0xEA20, SpecialCharacter("˘", false, 0));
	Pac::LatinTurkishOverrides.emplace(0xEA45, SpecialCharacter("Ĕ"));
	Pac::LatinTurkishOverrides.emplace(0xEA47, SpecialCharacter("Ğ"));
	Pac::LatinTurkishOverrides.emplace(0xEA49, SpecialCharacter("Ĭ"));
	Pac::LatinTurkishOverrides.emplace(0xEA4F, SpecialCharacter("Ŏ"));
	Pac::LatinTurkishOverrides.emplace(0xEA55, SpecialCharacter("Ŭ"));
	Pac::LatinTurkishOverrides.emplace(0xEA65, SpecialCharacter("ĕ"));
	Pac::LatinTurkishOverrides.emplace(0xEA67, SpecialCharacter("ğ"));
	Pac::LatinTurkishOverrides.emplace(0xEA69, SpecialCharacter("ĭ"));
	Pac::LatinTurkishOverrides.emplace(0xEA6F, SpecialCharacter("ŏ"));
	Pac::LatinTurkishOverrides.emplace(0xEA75, SpecialCharacter("ŭ"));
}


int Pac::FramesToMillisecondsMax999(double frames)
{
	int ms = static_cast<int>(BankersRounding::round(frames * (TimeCode::BaseUnit / Pac::GetFrameForCalculation(Configuration::getSettings()->General->getCurrentFrameRate()))));
	return ms < 999 ? ms : 999;
}

//std::optional<SpecialCharacter> Pac::GetNextArabicCharacter(u8Vector &buffer, int &index)
SpecialCharacter Pac::GetNextArabicCharacter(u8Vector& buffer, int& index)
{
	if ((size_t)index >= buffer.size())
	{
		//return std::nullopt;
		return SpecialCharacter();
	}

	unsigned char b = buffer[index];
	//	std::optional<SpecialCharacter> arabicCharacter;
	SpecialCharacter arabicCharacter;
	if (Pac::ArabicCodes.find(b) != Pac::ArabicCodes.end())
	{
		//arabicCharacter = std::make_optional(Pac::ArabicCodes[b]);
		arabicCharacter = Pac::ArabicCodes[b];
	}

	//if (arabicCharacter && buffer.size() > index + 1)
	if (arabicCharacter.Character.length() && buffer.size() > (size_t)index + 1)
	{
		auto code = b * 256 + buffer[index + 1];
		if (Pac::ArabicCodes.find(code) != Pac::ArabicCodes.end())
		{
			index++;
			arabicCharacter = Pac::ArabicCodes[code];
		}
	}

	//if (!arabicCharacter && b >= 0x20 && b < 0x70)
	if (!arabicCharacter.Character.length() && b >= 0x20 && b < 0x70)

	{
		return SpecialCharacter(getASCIIString(buffer, index, 1));
	}

	return arabicCharacter;
}

std::string Pac::GetHebrewString(u8Vector& buffer, int& index)
{
	unsigned char b = buffer[index];
	if (b >= 0x20 && b < 0x70 && b != 44)
	{
		return getASCIIString(buffer, index, 1);
	}

	if (Pac::HebrewCodes.find(b) != Pac::HebrewCodes.end())
	{
		return Pac::HebrewCodes[b].Character;
	}

	if (Pac::ThrowOnError)
	{
		throw InvalidOperationException(StringHelper::formatSimple("Unknown byte ({0}) in subtitle file @ binary offset {1}.", b, index));
	}

	return "";
}

bool Pac::TryGetMappedCharacter(std::unordered_map<int, SpecialCharacter>& map, u8Vector& buffer, int& index, std::string& result)
{
	unsigned char b = buffer[index];

	result = "";
	if (map.find(b) != map.end())
	{
		result = map[b].Character;
	}

	if (buffer.size() > (size_t)index + 2)
	{
		auto code = b * 256 + buffer[index + 1];
		auto next = buffer[index + 1] * 256 + buffer[index + 2];

		if (map.find(code) != map.end() && (map.find(next) == map.end() || map[code].Priority > map[next].Priority))
		{
			index++;
			result = map[code].Character;
		}
	}

	return !result.empty();
}

std::string Pac::GetCyrillicString(u8Vector& buffer, int& index)
{
	unsigned char b = buffer[index];

	if (b >= 0x30 && b <= 0x39) // decimal digits
	{
		return getASCIIString(buffer, index, 1);
	}

	if ((int) buffer.size() > index + 1)
	{
		auto code = b * 256 + buffer[index + 1];
		if (Pac::CyrillicCodes.find(code) != Pac::CyrillicCodes.end())
		{
			index++;
			return Pac::CyrillicCodes[code].Character;
		}
	}

	if (Pac::CyrillicCodes.find(b) != Pac::CyrillicCodes.end())
	{
		return Pac::CyrillicCodes[b].Character;
	}

	if (Pac::ThrowOnError)
	{
		throw InvalidOperationException(StringHelper::formatSimple("Unknown byte (0x{0:X2}) in subtitle file @ binary offset {1}.", b, index));
	}

	return "";
}

std::string Pac::GetGreekString(u8Vector& buffer, int& index)
{
	unsigned char b = buffer[index];

	if (b >= 0x30 && b <= 0x39) // decimal digits
	{
		return getASCIIString(buffer, index, 1);
	}

	if (Pac::GreekCodes.find(b) != Pac::GreekCodes.end())
	{
		return Pac::GreekCodes[b].Character;
	}

	if ((int) buffer.size() > index + 2)
	{
		int code = b * 65536 + buffer[index + 1] * 256 + buffer[index + 2];
		if (Pac::GreekCodes.find(code) != Pac::GreekCodes.end())
		{
			index += 2;
			return Pac::GreekCodes[code].Character;
		}

		code = b * 256 + buffer[index + 1];
		if (Pac::GreekCodes.find(code) != Pac::GreekCodes.end())
		{
			index++;
			return Pac::GreekCodes[code].Character;
		}
	}

	if (Pac::ThrowOnError)
	{
		throw InvalidOperationException(StringHelper::formatSimple("Unknown byte ({0}) in subtitle file @ binary offset {1}.", b, index));
	}
	return "";
}

//std::string Pac::GetLatinString(Encoding *encoding, u8Vector &buffer, int &index, std::unordered_map<int, SpecialCharacter> &overrides)
std::string Pac::GetLatinString(int code_page, u8Vector& buffer, int& index, std::unordered_map<int, SpecialCharacter>& overrides)
{
	::setCodePage(code_page);
	std::string result;
	if (!overrides.empty() && Pac::TryGetMappedCharacter(overrides, buffer, index, result))
	{
		return result;
	}

	if (Pac::TryGetMappedCharacter(Pac::LatinCodes, buffer, index, result))
	{
		return result;
	}

	if (buffer[index] > 13)
	{
		return getEncodedString(buffer, index, 1);
	}

	if (Pac::ThrowOnError)
	{
		throw InvalidOperationException(StringHelper::formatSimple("Unknown byte ({0}) in subtitle file @ binary offset {1}.", buffer[index], index));
	}

	return "";
}

std::string Pac::GetArabicString(u8Vector& buffer, int& index)
{
	auto arabicCharacter = Pac::GetNextArabicCharacter(buffer, index);

	//if (arabicCharacter && arabicCharacter.value().SwitchOrder)
	if (arabicCharacter.Character.length() && arabicCharacter.SwitchOrder)
	{
		// if we have a special character we must fetch the next one and move it before the current special one
		auto tempIndex = index + 1;
		auto nextArabicCharacter = Pac::GetNextArabicCharacter(buffer, tempIndex);
		//if (buffer[tempIndex] >= 0x80 && nextArabicCharacter)
		if (buffer[tempIndex] >= 0x80 && nextArabicCharacter.Character.length())
		{
			index = tempIndex;
			auto combined = StringHelper::formatSimple("{0}{1}", nextArabicCharacter.Character, arabicCharacter.Character);
			return combined;
		}
	}

	if (Pac::ThrowOnError && !arabicCharacter.Character.length())
	{
		throw InvalidOperationException(StringHelper::formatSimple("Unknown byte ({0}) in subtitle file @ binary offset {1}.", buffer[index], index));
	}

	return arabicCharacter.Character.length() ? arabicCharacter.Character : "";
}

TimeCode* Pac::GetTimeCode(int timeCodeIndex, u8Vector& buffer)
{
	if (timeCodeIndex > 0)
	{
		//	std::string highPart = std::string::Format("{0:000000}", buffer[timeCodeIndex] + buffer[timeCodeIndex + 1] * 256);
		//	std::string lowPart = std::string::Format("{0:000000}", buffer[timeCodeIndex + 2] + buffer[timeCodeIndex + 3] * 256);

		char time_str[10];
#ifdef WIN32
		sprintf_s(time_str, 10, "%06d", buffer[timeCodeIndex] + buffer[timeCodeIndex + 1] * 256);
#else
		sprintf(time_str, "%06d", buffer[timeCodeIndex] + buffer[timeCodeIndex + 1] * 256);
#endif
		std::string highPart = time_str;
#ifdef WIN32
		sprintf_s(time_str, 10, "%06d", buffer[timeCodeIndex + 2] + buffer[timeCodeIndex + 3] * 256);
#else
		sprintf(time_str, "%06d", buffer[timeCodeIndex + 2] + buffer[timeCodeIndex + 3] * 256);
#endif

		std::string lowPart = time_str;

		int hours = std::stoi(highPart.substr(0, 4));
		int minutes = std::stoi(highPart.substr(4, 2));
		int seconds = std::stoi(lowPart.substr(2, 2));
		int frames = std::stoi(lowPart.substr(4, 2));

		return new TimeCode(hours, minutes, seconds, Pac::FramesToMillisecondsMax999(frames));
	}
	return new TimeCode();
}
/*
Encoding *Pac::GetEncoding(int codePage)
{
	switch (codePage)
	{
		case Pac::CodePageLatin:
			return Encoding::GetEncoding("iso-8859-1");
		case Pac::CodePageGreek:
			return Encoding::GetEncoding("iso-8859-7");
		case Pac::CodePageLatinCzech:
			return Encoding::GetEncoding("iso-8859-2");
		case Pac::CodePageArabic:
			return Encoding::GetEncoding("iso-8859-6");
		case Pac::CodePageHebrew:
			return Encoding::GetEncoding("iso-8859-8");
		case Pac::CodePageLatinTurkish:
			return Encoding::GetEncoding("iso-8859-9");
		case Pac::CodePageThai:
			return Encoding::GetEncoding("windows-874");
		case Pac::CodePageCyrillic:
			return Encoding::GetEncoding("iso-8859-5");
		default:
			return Encoding::Default;
	}
}
*/
/*
int Pac::GetEncoding(int codePage_index)
{
	switch (codePage_index)
	{
	case Pac::CodePageLatin:
		return 28591;
		//return Encoding::GetEncoding("iso-8859-1");
	case Pac::CodePageGreek:
		return 28597;
		//return Encoding::GetEncoding("iso-8859-7");
	case Pac::CodePageLatinCzech:
		return 28592;
		//return Encoding::GetEncoding("iso-8859-2");
	case Pac::CodePageArabic:
		return 28596;
		//return Encoding::GetEncoding("iso-8859-6");
	case Pac::CodePageHebrew:
		return 28598;
		//return Encoding::GetEncoding("iso-8859-8");
	case Pac::CodePageLatinTurkish:
		return 28599;
		//return Encoding::GetEncoding("iso-8859-9");
	case Pac::CodePageThai:
		return 874;
		//return Encoding::GetEncoding("windows-874");
	case Pac::CodePageCyrillic:
		return 28595;
		//return Encoding::GetEncoding("iso-8859-5");
	default:
		return 28595;
		//return Encoding::Default;
	}
}
*/

int Pac::GetEncoding(int codePage_index)
{
	if(codePage_index == Pac::CodePageLatin)
		return 28591;
	else if(codePage_index ==  Pac::CodePageGreek)
		return 28597;
	else if(codePage_index ==  Pac::CodePageLatinCzech)
		return 28592;
	else if(codePage_index ==  Pac::CodePageArabic)
		return 28596;
	else if(codePage_index ==  Pac::CodePageHebrew)
		return 28598;
	else if(codePage_index ==  Pac::CodePageLatinTurkish)
		return 28599;
	else if(codePage_index ==  Pac::CodePageThai)
		return 874;
	else if(codePage_index ==  Pac::CodePageCyrillic)
		return 28595;
	else
		return 28595;

}

int Pac::AutoDetectEncoding(const std::string& fileName)
{
	printf("Pac::AutoDetectEncoding() is called. \n");

	if (Pac::s_This == nullptr)
	{
		return Pac::CodePageLatin;
	}
	//var pac = new Pac();
	try
	{
		auto dictionary = std::unordered_map<int, std::string>
		{
			{Pac::CodePageLatin, "en-da-no-sv-es-it-fr-pt-de-nl-pl-bg-sq-hr"},
			{Pac::CodePageGreek, "el"},
			{Pac::CodePageLatinCzech, "cz"},
			{Pac::CodePageLatinTurkish, "tr"},
			{Pac::CodePageArabic, "ar"},
			{Pac::CodePageHebrew, "he"},
			{Pac::CodePageThai, "th"},
			{Pac::CodePageCyrillic, "ru-uk-mk"},
			{Pac::CodePageChineseTraditional, "zh"},
			{Pac::CodePageChineseSimplified, "zh"},
			{Pac::CodePageKorean, "ko"},
			{Pac::CodePageJapanese, "ja"}
		};

		/*for (auto kvp : dictionary)
		{
			auto sub = new Subtitle();
			Pac::s_This->setCodePage(kvp.Key);
			Pac::s_This->LoadSubtitle(sub, std::vector<std::string>(), fileName);
			auto languageCode = LanguageAutoDetect::AutoDetectGoogleLanguageOrNull(sub);
			if (languageCode != "" && kvp.Value->Contains(languageCode))
			{
				return kvp.Key;
			}

		}*/
		std::unordered_map<int, std::string>::const_iterator iterator;
		for (iterator = dictionary.begin(); iterator != dictionary.end(); iterator++)
		{
			printf("Pac::AutoDetectEncoding() : setCodePage(%02d) is called \n", iterator->first);

			auto sub = new Subtitle();
			Pac::s_This->setCodePage(iterator->first);
			Pac::s_This->LoadSubtitle(&sub, fileName);
			auto languageCode = LanguageAutoDetect::AutoDetectGoogleLanguageOrNull(sub);
			if (languageCode != "" && iterator->second.find(languageCode))
			{
				return iterator->first;
			}
		}
	}
	catch (...)
	{
		// ignored
	}

	printf("Pac::AutoDetectEncoding() is finished. \n");
	return Pac::CodePageLatin;
}

void Pac::GetCodePage(u8Vector& buffer, int index, int endDelimiter)
{

	printf("Pac::GetCodePage() is called\n");

	if (Pac::s_This == nullptr)
	{
		return;
	}
	if (Pac::s_This->getBatchMode())
	{
		if (Pac::s_This->getCodePage() == -1)
		{
			Pac::s_This->setCodePage(AutoDetectEncoding(Pac::s_This->_fileName));
		}

		return;
	}

	printf("Pac::GetCodePage() : No BatchMode... \n");

	u8Vector previewBuffer;
	if (!buffer.empty())
	{
		auto textSample = u8Vector(200);
		uint textIndex = 0;
		while (index < (int) buffer.size() && buffer[index] != endDelimiter)
		{
			if (buffer[index] == 0xFF)
			{
				if (textIndex < textSample.size() - 1)
				{
					textSample[textIndex++] = 32; // ASCII 32 SP (Space)
				}

				index++;
			}
			else if (buffer[index] == 0xFE)
			{
				if (textIndex < textSample.size() - 3)
				{
					textSample[textIndex++] = buffer[index];
					textSample[textIndex++] = buffer[index + 1];
					textSample[textIndex++] = buffer[index + 2];
				}
				index += 3;
			}
			else
			{
				if (textIndex < textSample.size() - 1)
				{
					textSample[textIndex++] = buffer[index];
				}

				index++;
			}
		}
		previewBuffer = u8Vector(textIndex);
		for (uint i = 0; i < textIndex; i++)
		{
			previewBuffer[i] = textSample[i];
		}
	}

	//	int tempVar = Pac::GetPacEncodingImplementation.GetPacEncoding(previewBuffer, Pac.s_This._fileName);
	//	Pac::s_This->setCodePage(Pac::GetPacEncodingImplementation == nullptr ? nullptr : (tempVar != nullptr) ? tempVar : 2);

	printf("Pac::GetCodePage(u8vector, int, int) is finished. \n");

	// int tempVar = Pac::GetPacEncodingImplementation->GetPacEncoding(previewBuffer, Pac::s_This->_fileName);
	// Pac::s_This->setCodePage(tempVar ? tempVar : 2);
	return;
}


std::string Pac::FixItalics(const std::string& input)
{
	std::string pre = "";
	std::string text = input;
	if (text.substr(0, 2) == "{\\")
	{
		auto endIdx = (int)text.find('}', 2);
		if (endIdx > 2)
		{
			pre = text.substr(0, endIdx + 1);
			text.erase(0, endIdx + 1);
		}
	}
	int index = (int)text.find('<');
	if (index < 0)
	{
		return input;
	}

	while (index >= 0 && index < (int) text.length() - 1)
	{
		text.insert(index + 1, "i>");
		int indexOfNewLine = (int)text.find("\r\n", index + 3);
		int indexOfEnd = (int)text.find('>', index + 3);
		if (indexOfNewLine < 0 && indexOfEnd < 0)
		{
			index = -1;
			text += "</i>";
		}
		else
		{
			if (indexOfNewLine < 0 || (indexOfEnd > 0 && indexOfEnd < indexOfNewLine))
			{
				text.insert(indexOfEnd, "</i");
				index = (int)text.find('<', indexOfEnd + 3);
			}
			else
			{
				text.insert(indexOfNewLine, "</i>");
				index = (int)text.find('<', indexOfNewLine + 4);
			}
		}
	}
	text = StringHelper::replace(text, "</i>", "</i> ");
	text = StringHelper::replace(text, "  ", " ");
	return pre + StringHelper::trim(StringHelper::replace(text, std::string(" ") + "\r\n", "\r\n"));
}

void Pac::LoadSubtitle(Subtitle* subtitle, u8Vector& buffer)
{
	subtitle->Paragraphs.clear();
	subtitle->Header.clear();

	bool usesSecondaryCodePage = Pac::UsesSecondaryCodePage(buffer);
	int index = 0;
	while (index < (int) buffer.size())
	{
		Paragraph* p = Pac::GetPacParagraph(index, buffer, usesSecondaryCodePage);
		if (p != nullptr)
		{
			subtitle->Paragraphs.push_back(p);
		}
	}
	subtitle->Renumber();
}


StringBuilder* Pac::ProcessLoopInsideGetPacParagraph(int index, u8Vector& buffer, int maxIndex, unsigned char& alignment, bool& isSecondaryCodePage, int CodePage, bool usesSecondaryCodePage)
{
	auto overrides = (CodePage == Pac::CodePageLatinTurkish) ? Pac::LatinTurkishOverrides : std::unordered_map<int, SpecialCharacter>();
	auto sb = new StringBuilder();
	//std::string sb;
	bool w16 = buffer[index] == 0x1f && getASCIIString(buffer, index + 1, 3) == "W16";

	if (w16)
	{
		index += 5;
	}

	while (index < (int) buffer.size() && index <= maxIndex) // buffer[index] != endDelimiter)
	{
		if ((int) buffer.size() > index + 3 && buffer[index] == 0x1f && getASCIIString(buffer, index + 1, 3) == "W16")
		{
			w16 = true;
			index += 5;
		}
		else if ((int) buffer.size() > index + 2 && buffer[index] == 0x1f && buffer[index + 1] == 'C' && std::isdigit(static_cast<char>(buffer[index + 2])))
		{
			index += 3;
			continue;
		}

		if (w16)
		{
			if (buffer[index] == 0xFE)
			{
				alignment = buffer[index + 1];
				isSecondaryCodePage = (alignment & 0x08) != 0;
				alignment &= 0x07;
				sb->appendLine();

				w16 = buffer[index + 3] == 0x1f && getASCIIString(buffer, index + 4, 3) == "W16";
				if (w16)
				{
					index += 5;
				}

				index += 2;
			}
			else
			{
				if (buffer[index] == 0)
				{
					sb->append(getASCIIString(buffer, index + 1, 1));
				}
				else if ((int) buffer.size() > index + 1)
				{
					if (CodePage == Pac::CodePageChineseSimplified)
					{
						//sb.append(Encoding::GetEncoding(Pac::EncodingChineseSimplified)->GetString(buffer, index, 2));
						sb->append(getW16EncodedString(Pac::EncodingChineseSimplified, buffer, index, 2));
					}
					else if (CodePage == Pac::CodePageKorean)
					{
						//sb.append(Encoding::GetEncoding(Pac::EncodingKorean)->GetString(buffer, index, 2));
						sb->append(getW16EncodedString(Pac::EncodingKorean, buffer, index, 2));
					}
					else if (CodePage == Pac::CodePageJapanese)
					{
						//sb.append(Encoding::GetEncoding(Pac::EncodingJapanese)->GetString(buffer, index, 2));
						sb->append(getW16EncodedString(Pac::EncodingJapanese, buffer, index, 2));
					}
					else
					{
						//sb.append(Encoding::GetEncoding(Pac::EncodingChineseTraditional)->GetString(buffer, index, 2));
						sb->append(getW16EncodedString(Pac::EncodingChineseTraditional, buffer, index, 2));
					}
				}

				index++;
			}
		}
		else if (buffer[index] == 0xFF)
		{
			sb->append(' ');
		}
		else if (buffer[index] == 0xFE)
		{
			alignment = buffer[index + 1];
			isSecondaryCodePage = (alignment & 0x08) != 0;
			alignment &= 0x07;
			sb->appendLine();
			//sb += "\n";
			index += 2;
		}
		else if (CodePage == Pac::CodePageLatin || CodePage == Pac::CodePageLatinTurkish || CodePage == Pac::CodePageLatinCzech || (usesSecondaryCodePage && !isSecondaryCodePage))
		{
			sb->append(Pac::GetLatinString(Pac::GetEncoding(CodePage), buffer, index, overrides));
		}
		else if (CodePage == Pac::CodePageArabic)
		{
			sb->append(Pac::GetArabicString(buffer, index));
		}
		else if (CodePage == Pac::CodePageHebrew)
		{
			sb->append(Pac::GetHebrewString(buffer, index));
		}
		else if (CodePage == Pac::CodePageCyrillic)
		{
			sb->append(Pac::GetCyrillicString(buffer, index));
		}
		else if (CodePage == Pac::CodePageGreek)
		{
			sb->append(Pac::GetGreekString(buffer, index));
		}
		else if (CodePage == Pac::CodePageThai)
		{
			//sb.append(StringHelper::replace(Pac::GetEncoding(CodePage)->GetString(buffer, index, 1), "€", "ต"));
			sb->append(StringHelper::replace(getW16EncodedString(Pac::EncodingThai, buffer, index, 1), "€", "ต"));
		}
		else
		{
			//sb.append(Pac::GetEncoding(CodePage)->GetString(buffer, index, 1));
			sb->append(getEncodedString(Pac::GetEncoding(CodePage), buffer, index, 1));
		}

		index++;
	}
	if (index + 20 >= (int)buffer.size())
	{
		//delete sb;
		return nullptr;
	}

	//C# TO C++ CONVERTER TODO TASK: A 'delete sb' statement was not added since sb was used in a 'return' or 'throw' statement.
	return sb;
}



bool Pac::ProcessLastPart(StringBuilder* sb, int CodePage, unsigned char verticalAlignment, Paragraph*& p, unsigned char alignment)
{
	p->Text = sb->toString();
	//p->Text = StringHelper::replace(p->Text, "\0", "");

	p->Text = Pac::FixItalics(p->Text);
	if (CodePage == Pac::CodePageArabic)
	{
		p->Text = Utilities::FixEnglishTextInRightToLeftLanguage(p->Text, "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	}
	else if (CodePage == Pac::CodePageHebrew)
	{
		p->Text = Utilities::FixEnglishTextInRightToLeftLanguage(p->Text, "0123456789abcdefghijklmnopqrstuvwxyz");
	}

	if (verticalAlignment < 5)
	{
		if (alignment == 1) // left
		{
			p->Text = "{\\an7}" + p->Text;
		}
		else if (alignment == 0) // right
		{
			p->Text = "{\\an9}" + p->Text;
		}
		else
		{
			p->Text = "{\\an8}" + p->Text;
		}
	}
	else if (verticalAlignment < 9)
	{
		if (alignment == 1) // left
		{
			p->Text = "{\\an4}" + p->Text;
		}
		else if (alignment == 0) // right
		{
			p->Text = "{\\an6}" + p->Text;
		}
		else
		{
			p->Text = "{\\an5}" + p->Text;
		}
	}
	else
	{
		if (alignment == 1) // left
		{
			p->Text = "{\\an1}" + p->Text;
		}
		else if (alignment == 0) // right
		{
			p->Text = "{\\an3}" + p->Text;
		}
	}
	p->Text = StringExtensions::RemoveControlCharactersButWhiteSpace(p->Text);
	return true;
}


int Pac::ProcessStartEndTime(Paragraph*& p, u8Vector& buffer, int timeStartIndex)
{
	if (buffer[timeStartIndex] == 0x60)
	{
		p->StartTime = Pac::GetTimeCode(timeStartIndex + 1, buffer);
		p->EndTime = Pac::GetTimeCode(timeStartIndex + 5, buffer);
	}
	else if (buffer[timeStartIndex + 3] == 0x60)
	{
		timeStartIndex += 3;
		p->StartTime = Pac::GetTimeCode(timeStartIndex + 1, buffer);
		p->EndTime = Pac::GetTimeCode(timeStartIndex + 5, buffer);
	}
	else if (buffer[timeStartIndex] == 0x61)
	{
		p->StartTime = Pac::GetTimeCode(timeStartIndex + 1, buffer);
		p->EndTime = Pac::GetTimeCode(timeStartIndex + 5, buffer);
		int length = buffer[timeStartIndex + 9] + buffer[timeStartIndex + 10] * 256;
		if (length < 1 || length > 200 || p->StartTime->getTotalSeconds() - Pac::_lastStartTotalSeconds < 1 || p->StartTime->getTotalSeconds() - Pac::_lastStartTotalSeconds > 1500 || p->EndTime->getTotalSeconds() - Pac::_lastEndTotalSeconds < 1 || p->EndTime->getTotalSeconds() - Pac::_lastEndTotalSeconds > 1500)
		{
			return -1;
		}
	}
	else if (buffer[timeStartIndex + 3] == 0x61)
	{
		timeStartIndex += 3;
		p->StartTime = Pac::GetTimeCode(timeStartIndex + 1, buffer);
		p->EndTime = Pac::GetTimeCode(timeStartIndex + 5, buffer);
		int length = buffer[timeStartIndex + 9] + buffer[timeStartIndex + 10] * 256;
		if (length < 1 || length > 200 || p->StartTime->getTotalSeconds() - Pac::_lastStartTotalSeconds < 1 || p->StartTime->getTotalSeconds() - Pac::_lastStartTotalSeconds > 1500 || p->EndTime->getTotalSeconds() - Pac::_lastEndTotalSeconds < 1 || p->EndTime->getTotalSeconds() - Pac::_lastEndTotalSeconds > 1500)
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
	int textLength = buffer[timeStartIndex + 9] + buffer[timeStartIndex + 10] * 256;
	if (textLength > 500)
	{
		return -1;
	}

	Pac::_lastStartTotalSeconds = p->StartTime->getTotalSeconds();
	Pac::_lastEndTotalSeconds = p->EndTime->getTotalSeconds();

	return textLength;
}

bool Pac::ProcessCheckBuffer(int& index, u8Vector& buffer)
{
	bool isStory = index < 15;
	if (isStory)
	{
		index = 15;
	}

	while (true)
	{
		index++;
		if (index + 20 >= (int) buffer.size())
		{
			return false;
		}

		if (buffer[index] == 0xFE && (buffer[index - 15] == 0x60 || buffer[index - 15] == 0x61))
		{
			break;
		}

		if (buffer[index] == 0xFE && (buffer[index - 12] == 0x60 || buffer[index - 12] == 0x61))
		{
			break;
		}
	}

	return true;
}


double Pac::_lastStartTotalSeconds = 0;
double Pac::_lastEndTotalSeconds = 0;

Paragraph* Pac::GetPacParagraph(int& index, u8Vector& buffer, bool usesSecondaryCodePage)
{
	if (Pac::s_This == nullptr)
	{
		return nullptr;
	}
	if (!Pac::ProcessCheckBuffer(index, buffer))
	{
		return nullptr;
	}

	int feIndex = index;
	constexpr int endDelimiter = 0x00;
	unsigned char alignment = buffer[feIndex + 1];
	bool isSecondaryCodePage = (alignment & 0x08) != 0;
	alignment &= 0x07;

	auto p = new Paragraph();
	int timeStartIndex = feIndex - 15;

	int textLength = Pac::ProcessStartEndTime(p, buffer, timeStartIndex);
	if (textLength < 0)
	{
		//C# TO C++ CONVERTER TODO TASK: A 'delete p' statement was not added since p was passed to a method or constructor. Handle memory management manually.
		return nullptr;
	}

	int maxIndex = timeStartIndex + 10 + textLength;
	unsigned char verticalAlignment = buffer[timeStartIndex + 11];

	if (Pac::s_This->getCodePage() == -1)
	{
		Pac::GetCodePage(buffer, index, endDelimiter);
	}

	StringBuilder* sb = Pac::ProcessLoopInsideGetPacParagraph(index, buffer, maxIndex, alignment, isSecondaryCodePage, Pac::s_This->getCodePage(), usesSecondaryCodePage);
	Pac::ProcessLastPart(sb, Pac::s_This->getCodePage(), verticalAlignment, p, alignment);

	//C# TO C++ CONVERTER TODO TASK: A 'delete p' statement was not added since p was passed to a method or constructor. Handle memory management manually.
	return p;
}

bool Pac::UsesSecondaryCodePage(u8Vector& buffer)
{
	bool firstIsSecondary = false;
	bool isInited = false;
	int secondaryUse = 0;
	for (int i = 15; i < (int) buffer.size() - 1; i++)
	{
		if (buffer[i] == 0xFE && (buffer[i - 15] == 0x60 || buffer[i - 15] == 0x61 || buffer[i - 12] == 0x60 || buffer[i - 12] == 0x61))
		{
			bool secondary = (buffer[i + 1] & 0x08) != 0;
			firstIsSecondary = isInited ? firstIsSecondary : secondary;
			isInited = true;
			if (secondary)
			{
				secondaryUse++;
			}
		}
	}

	return secondaryUse > (firstIsSecondary ? 1 : 0);
}
