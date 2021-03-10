#pragma once

#include "SubtitleFormat.h"
#include "../libse/Subtitle.h"
#include <string>
#include <vector>
#include <regex>
#include "../../common/stringhelper.h"

class Ebu : public SubtitleFormat
{
public:
    Ebu();

    /// <summary>
    /// GSI block (1024 bytes)
    /// </summary>
    class EbuGeneralSubtitleInformation 
    {
    public:
        EbuGeneralSubtitleInformation();
        double FrameRate();
        std::string ToString();

    public:
        std::string CodePageNumber;
        std::string DiskFormatCode;
        double      FrameRateFromSaveDialog;
        std::string DisplayStandardCode;
        std::string CharacterCodeTableNumber;
        std::string LanguageCode;
        std::string OriginalProgrammeTitle;
        std::string OriginalEpisodeTitle;
        std::string TranslatedProgrammeTitle;
        std::string TranslatedEpisodeTitle;
        std::string TranslatorsName;
        std::string TranslatorsContactDetails;
        std::string SubtitleListReferenceCode;
        std::string CreationDate;
        std::string RevisionDate;
        std::string RevisionNumber;
        std::string TotalNumberOfTextAndTimingInformationBlocks;
        std::string TotalNumberOfSubtitles;
        std::string TotalNumberOfSubtitleGroups;
        std::string MaximumNumberOfDisplayableCharactersInAnyTextRow;
        std::string MaximumNumberOfDisplayableRows;
        std::string TimeCodeStatus;
        std::string TimeCodeStartOfProgramme;
        std::string TimeCodeFirstInCue;
        std::string TotalNumberOfDisks;
        std::string DiskSequenceNumber;
        std::string CountryOfOrigin;
        std::string Publisher;
        std::string EditorsName;
        std::string EditorsContactDetails;
        std::string SpareBytes;
        std::string UserDefinedArea;
    };

    class EbuTextTimingInformation
    {
    public:
        EbuTextTimingInformation();

    public:
        byte SubtitleGroupNumber;
        ushort SubtitleNumber;
        byte ExtensionBlockNumber;
        byte CumulativeStatus;
        int TimeCodeInHours;
        int TimeCodeInMinutes;
        int TimeCodeInSeconds;
        int TimeCodeInMilliseconds;
        int TimeCodeOutHours;
        int TimeCodeOutMinutes;
        int TimeCodeOutSeconds;
        int TimeCodeOutMilliseconds;
        byte VerticalPosition;
        byte JustificationCode;
        byte CommentFlag;
        std::string TextField;
    };

public:
	std::string getExtension() const ;
    static const std::string NameOfFormat;
    static const double BaseUnit; // Base unit of time
	std::string getName() const ;
    bool getIsTimeBased() const ;

    bool IsMine( const std::string& fileName);// override;

    std::string ToText(Subtitle* subtitle, const std::string& title);// override;

    bool probe(std::istream& istrm);
	Subtitle* LoadSubtitle(std::istream& isrm);
	void LoadSubtitle(Subtitle** subtitle, const std::string& fileName);// override;
    
    EbuGeneralSubtitleInformation ReadHeader(u8Vector buffer);
    std::vector<Ebu::EbuTextTimingInformation> ReadTextAndTiming(u8Vector buffer, Ebu::EbuGeneralSubtitleInformation header);

private:    
    double GetFrameForCalculation(double frameRate);
    int FramesToMillisecondsMax999(int frames, double currentFrameRate);
    std::string GetCharacter(bool &skipNext, EbuGeneralSubtitleInformation header, u8Vector buffer, int index);
private:
    static std::string LanguageCodeChinese;

    std::vector<int> VerticalPositions;
    std::vector<int> JustificationCodes;

    EbuGeneralSubtitleInformation Header;
};

