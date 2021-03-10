#pragma once

#include "Subtitle.h"
#include <string>
#include <vector>

class LanguageAutoDetect final
{
public:
	static int GetCount(const std::string &text, std::vector<std::string> &words);

	static int GetCountContains(const std::string &text, std::vector<std::string> &words);

	static std::string AutoDetectGoogleLanguage1(const std::string& text, int bestCount);
	static std::string AutoDetectGoogleLanguage2(const std::string& text, int bestCount);
	static std::string AutoDetectGoogleLanguage3(const std::string& text, int bestCount);


	static std::string GetEncodingViaLetter(const std::string& text);


//public:

	static std::string AutoDetectGoogleLanguage(const std::string& text, int bestCount);

	static std::string AutoDetectGoogleLanguageOrNull(Subtitle *subtitle);

	static std::string GetEncodingViaLetterD(const std::string &text);


	static std::vector<std::string> AutoDetectWordsEnglish;

	static std::vector<std::string> AutoDetectWordsDanish;

	static std::vector<std::string> AutoDetectWordsNorwegian;

	static std::vector<std::string> AutoDetectWordsSwedish;
	static std::vector<std::string> AutoDetectWordsSpanish;

	static std::vector<std::string> AutoDetectWordsItalian;

	static std::vector<std::string> AutoDetectWordsFrench;

	static std::vector<std::string> AutoDetectWordsPortuguese;

	static std::vector<std::string> AutoDetectWordsGerman;

	static std::vector<std::string> AutoDetectWordsDutch;

	static std::vector<std::string> AutoDetectWordsPolish;

	static std::vector<std::string> AutoDetectWordsGreek;

	static std::vector<std::string> AutoDetectWordsRussian;

	static std::vector<std::string> AutoDetectWordsBulgarian;

	static std::vector<std::string> AutoDetectWordsUkrainian;
	
	static std::vector<std::string> AutoDetectWordsAlbanian;

	static std::vector<std::string> AutoDetectWordsArabic;

	static std::vector<std::string> AutoDetectWordsFarsi;

	static std::vector<std::string> AutoDetectWordsHebrew;

	static std::vector<std::string> AutoDetectWordsVietnamese;

	static std::vector<std::string> AutoDetectWordsHungarian;

	static std::vector<std::string> AutoDetectWordsTurkish;

	static std::vector<std::string> AutoDetectWordsCroatianAndSerbian;
	
	static std::vector<std::string> AutoDetectWordsCroatian;
	
	static std::vector<std::string> AutoDetectWordsSerbian;

	static std::vector<std::string> AutoDetectWordsSerbianCyrillic;

	static std::vector<std::string> AutoDetectWordsIndonesian;

	static std::vector<std::string> AutoDetectWordsThai;

	static std::vector<std::string> AutoDetectWordsKorean;

	static std::vector<std::string> AutoDetectWordsMacedonian;

	static std::vector<std::string> AutoDetectWordsFinnish;

	static std::vector<std::string> AutoDetectWordsRomanian;

	// Czech and Slovak languages have many common words (especially when non flexed)
	static std::vector<std::string> AutoDetectWordsCzechAndSlovak;
	// differences between Czech and Slovak languages / Czech words / please keep the words aligned between these languages for better comparison
	static std::vector<std::string> AutoDetectWordsCzech;
	// differences between Czech and Slovak languages / Slovak words / please keep the words aligned between these languages for better comparison
	static std::vector<std::string> AutoDetectWordsSlovak;

	static std::vector<std::string> AutoDetectWordsLatvian;

	static std::vector<std::string> AutoDetectWordsLithuanian;

	static std::vector<std::string> AutoDetectWordsHindi;

	static std::vector<std::string> AutoDetectWordsUrdu;

	static std::vector<std::string> AutoDetectWordsSinhalese;

};
