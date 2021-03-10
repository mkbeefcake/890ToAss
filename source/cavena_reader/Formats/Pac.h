#pragma once

#include "SubtitleFormat.h"
#include "../libse/TimeCode.h"
#include "../libse/Subtitle.h"
#include "../../common/define.h"
//#include "../tangible_filesystem.h"
class SpecialCharacter
{
public:
	SpecialCharacter(const std::string& character, bool switchOrder = false, int priority = 2);

	std::string Character = "";
	bool SwitchOrder = false;
	int Priority = 0;

	SpecialCharacter() = default;
};
class IGetPacEncoding
{
public:
	virtual int GetPacEncoding(u8Vector& previewBuffer, const std::string& fileName) = 0;
};

class Pac : public SubtitleFormat
{
private:
	int CodePage = -1;

public:
	static Pac *s_This;

	Pac();

public:

	static void AddArabicCodes();
	static std::unordered_map<int, SpecialCharacter> LatinCodes;
	static std::unordered_map<int, SpecialCharacter> LatinTurkishOverrides;
	static std::unordered_map<int, SpecialCharacter> HebrewCodes;
	static std::unordered_map<int, SpecialCharacter> ArabicCodes;
	static std::unordered_map<int, SpecialCharacter> CyrillicCodes;
	static std::unordered_map<int, SpecialCharacter> KoreanCodes;

	static std::unordered_map<int, SpecialCharacter> GreekCodes;

	static void InitializeVariables();

	static int CodePageLatin;
	static int CodePageGreek;
	static int CodePageLatinCzech;
	static int CodePageArabic;
	static int CodePageHebrew;
	static int CodePageThai;
	static int CodePageCyrillic;
	static int CodePageChineseTraditional;
	static int CodePageChineseSimplified;
	static int CodePageKorean;
	static int CodePageJapanese;
	static int CodePageLatinTurkish;

	static int EncodingChineseSimplified;
	static int EncodingChineseTraditional;
	static int EncodingKorean;
	static int EncodingJapanese;

	static void AddCyrillicCodes1();
	static void AddCyrillicCodes2();
	static void AddCyrillicCodes3();
	static void AddGreekCodes1();
	static void AddGreekCodes2();
	static void AddGreekCodes3();
	static void AddHebrewCode();
	static void AddLatinCodes1();
	static void AddLatinCodes2();
	static void AddLatinCodes3();
	static void AddLatinCodes4();
	static void AddTurkishLatinCodes();

	static int FramesToMillisecondsMax999(double frames);

	static SpecialCharacter GetNextArabicCharacter(u8Vector& buffer, int& index);

	static std::string GetHebrewString(u8Vector& buffer, int& index);

	static bool TryGetMappedCharacter(std::unordered_map<int, SpecialCharacter>& map, u8Vector& buffer, int& index, std::string& result);

	static std::string GetCyrillicString(u8Vector& buffer, int& index);

	static std::string GetGreekString(u8Vector& buffer, int& index);

	//static std::string GetLatinString(Encoding *encoding, u8Vector &buffer, int &index, std::unordered_map<int, SpecialCharacter> &overrides);
	static std::string GetLatinString(int code_page, u8Vector& buffer, int& index, std::unordered_map<int, SpecialCharacter>& overrides);
	static std::string GetArabicString(u8Vector& buffer, int& index);

	static TimeCode* GetTimeCode(int timeCodeIndex, u8Vector& buffer);


	//static Encoding *GetEncoding(int codePage);
	static int GetEncoding(int codePage_index);

	static int AutoDetectEncoding(const std::string& fileName);

	static void GetCodePage(u8Vector& buffer, int index, int endDelimiter);

	static std::string FixItalics(const std::string& input);

	static void LoadSubtitle(Subtitle* subtitle, u8Vector& buffer);

	static StringBuilder* ProcessLoopInsideGetPacParagraph(int index, u8Vector& buffer, int maxIndex, unsigned char& alignment, bool& isSecondaryCodePage, int CodePage, bool usesSecondaryCodePage);

	static bool ProcessLastPart(StringBuilder* sb, int CodePage, unsigned char verticalAlignment, Paragraph*& p, unsigned char alignment);

	static int ProcessStartEndTime(Paragraph*& p, u8Vector& buffer, int timeStartIndex);

	static bool ProcessCheckBuffer(int& index, u8Vector& buffer);

	static double _lastStartTotalSeconds;
	static double _lastEndTotalSeconds;

	static Paragraph* GetPacParagraph(int& index, u8Vector& buffer, bool usesSecondaryCodePage);

	static bool UsesSecondaryCodePage(u8Vector& buffer);

public:
	static IGetPacEncoding *GetPacEncodingImplementation;

	static TimeCode *PacNullTime;

	static bool ThrowOnError;

	std::string _fileName = "";

	int getCodePage() const;
	void setCodePage(int value);

	std::string getExtension() const override;

	static const std::string NameOfFormat;

	std::string getName() const override;

	bool IsMine(const std::string &fileName) override;

    Subtitle* LoadSubtitle(std::istream& isrm);
	void LoadSubtitle(Subtitle **subtitle, const std::string &fileName) override;

	std::string ToText(Subtitle *subtitle, const std::string &title) override;
};
