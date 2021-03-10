#pragma once

#include "SubtitleFormat.h"
#include "../libse/Subtitle.h"
#include <string>
#include <vector>
#include "../../common/stringhelper.h"

class Cavena890 : public SubtitleFormat
{
public:
	std::string getExtension() const ;
	static const std::string NameOfFormat;
	std::string getName() const ;
	bool getIsTimeBased() const ;

	static constexpr int LanguageIdDanish = 0x07;
	static constexpr int LanguageIdEnglish = 0x09;
	static constexpr int LanguageIdRussian = 0x56;
	static constexpr int LanguageIdArabic = 0x80;
	static constexpr int LanguageIdHebrew = 0x8f;
	static constexpr int LanguageIdChineseTraditional = 0x90;
	static constexpr int LanguageIdChineseSimplified = 0x91;
	static constexpr int LanguageIdRomanian = 0x22;

private:
	int _languageIdLine1 = LanguageIdEnglish;
	int _languageIdLine2 = LanguageIdEnglish;
	static std::unordered_map<int, std::string> ArabicDictionary;
	static std::vector<int> HebrewCodes;
	static std::vector<std::string> HebrewLetters;

	static std::vector<int> RussianCodes;

	static std::vector<std::string> RussianLetters;
public:
	
	Cavena890();

	bool IsMine( const std::string& fileName);// override;

	std::string ToText(Subtitle* subtitle, const std::string& title);// override;

	bool probe(std::istream& isrm);
	Subtitle* LoadSubtitle(std::istream& isrm);
	void LoadSubtitle(Subtitle** subtitle, const std::string& fileName);// override;

	static std::string FixText(u8Vector& buffer, int start, int textLength, int languageId);
	static std::string FixColors(const std::string& text);
	static std::string FixTextOtherCase(u8Vector& buffer, int start, int textLength);
	static std::string FixTextOtherCase2(const std::string& szText);
	static std::string FixTextArabic(u8Vector& buffer, int start, int textLength);

	static std::string FixTextTraditional(u8Vector& buffer, int start, int textLength);

	static std::string ReverseAnsi(const std::string& text,std::vector<bool> b_heb_vec);
};
