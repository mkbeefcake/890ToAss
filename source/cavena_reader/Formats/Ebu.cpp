#include "Ebu.h"
#include "../libse/FileUtil.h"
#include "../libse/Paragraph.h"
#include "../libse/Configuration.h"
#include "../libse/TimeCode.h"
#include "../libse/StringExtensions.h"
#include "../libse/Utilities.h"
#include "../../my_api.h"
#include <unistd.h>
#include <fstream>
#include <cmath>
#include <algorithm>

std::string Ebu::LanguageCodeChinese = "75";

Ebu::EbuGeneralSubtitleInformation::EbuGeneralSubtitleInformation()
{
    CodePageNumber = "437";
    DiskFormatCode = "STL25.01";
    DisplayStandardCode = "0"; // 0 = open subtitling
    CharacterCodeTableNumber = "00";
    LanguageCode = "0A";
    OriginalProgrammeTitle = "No Title                        ";
    OriginalEpisodeTitle = "                                ";
    TranslatedProgrammeTitle = StringExtensions::PadLeft("", 32, ' ');
    TranslatedEpisodeTitle = StringExtensions::PadLeft("", 32, ' ');
    TranslatorsName = StringExtensions::PadLeft("", 32, ' ');
    TranslatorsContactDetails = StringExtensions::PadLeft("", 32, ' ');
    SubtitleListReferenceCode = "0               ";
    CreationDate = "101021";
    RevisionDate = "101021";
    RevisionNumber = "01";
    TotalNumberOfTextAndTimingInformationBlocks = "00725";
    TotalNumberOfSubtitles = "00725";
    TotalNumberOfSubtitleGroups = "001";
    MaximumNumberOfDisplayableCharactersInAnyTextRow = "40";
    MaximumNumberOfDisplayableRows = "23";
    TimeCodeStatus = "1";
    TimeCodeStartOfProgramme = "00000000";
    TimeCodeFirstInCue = "00000001";
    TotalNumberOfDisks = "1";
    DiskSequenceNumber = "1";
    CountryOfOrigin = "USA";
    Publisher = StringExtensions::PadLeft("", 32, ' ');
    EditorsName = StringExtensions::PadLeft("", 32, ' ');
    EditorsContactDetails = StringExtensions::PadLeft("", 32, ' ');
    SpareBytes = StringExtensions::PadLeft("", 75, ' ');
    UserDefinedArea = StringExtensions::PadLeft("", 576, ' ');
}

double Ebu::EbuGeneralSubtitleInformation::FrameRate()
{
    if (FrameRateFromSaveDialog > 20) {
        return FrameRateFromSaveDialog;
    }

    if (StringExtensions::StartsWith(DiskFormatCode, "STL23")) {
        return 23.0;
    }

    if (StringExtensions::StartsWith(DiskFormatCode, "STL24")) {
        return 24.0;
    }

    if (StringExtensions::StartsWith(DiskFormatCode, "STL25")) {
        return 25.0;
    }

    if (StringExtensions::StartsWith(DiskFormatCode, "STL29")) {
        return 29.0;
    }

    if (StringExtensions::StartsWith(DiskFormatCode, "STL35")) {
        return 35.0;
    }

    if (StringExtensions::StartsWith(DiskFormatCode, "STL48")) {
        return 48.0;
    }

    if (StringExtensions::StartsWith(DiskFormatCode, "STL50")) {
        return 50.0;
    }

    if (StringExtensions::StartsWith(DiskFormatCode, "STL60")) {
        return 60.0;
    }

    return 30.0;    // should be DiskFormatCode STL30.01
}

std::string Ebu::EbuGeneralSubtitleInformation::ToString()
{
    std::string result;
    result = CodePageNumber + 
             DiskFormatCode + 
             DisplayStandardCode +
             CharacterCodeTableNumber + 
             LanguageCode +
             OriginalProgrammeTitle +
             OriginalEpisodeTitle +
             TranslatedProgrammeTitle +
             TranslatedEpisodeTitle + 
             TranslatorsName + 
             TranslatorsContactDetails +
             SubtitleListReferenceCode +
             CreationDate +
             RevisionDate +
             RevisionNumber +
             TotalNumberOfTextAndTimingInformationBlocks +
             TotalNumberOfSubtitles +
             TotalNumberOfSubtitleGroups +
             MaximumNumberOfDisplayableCharactersInAnyTextRow +
             MaximumNumberOfDisplayableRows +
             TimeCodeStatus +
             TimeCodeStartOfProgramme +
             TimeCodeFirstInCue + 
             TotalNumberOfDisks +
             DiskSequenceNumber + 
             CountryOfOrigin + 
             Publisher + 
             EditorsName + 
             EditorsContactDetails + 
             SpareBytes + 
             UserDefinedArea;

    if (result.length() == 1024) {
        return result;
    }

    return "Length must be 1024 but is " + result.length();
}

Ebu::EbuTextTimingInformation::EbuTextTimingInformation()
{
    SubtitleGroupNumber = (byte)0;
    ExtensionBlockNumber = (byte)255;
    CumulativeStatus = (byte)0;
    VerticalPosition = (byte)0x16;
    JustificationCode = (byte)2;
    CommentFlag = (byte)0;
}

Ebu::Ebu()
{
    // printf("Ebu::Ebu() is called\n");
}

std::string Ebu::getExtension() const
{
    return ".STL";
}

const std::string Ebu::NameOfFormat = "EBU STL";
const double Ebu::BaseUnit = 1000.0;

std::string Ebu::getName() const
{
    return NameOfFormat;
}

std::string Ebu::ToText(Subtitle *subtitle, const std::string &title)
{
    // to avoid -Wunused-parameter
    UNUSED(subtitle);
    UNUSED(title);

    return "Not supported!";
}

Ebu::EbuGeneralSubtitleInformation Ebu::ReadHeader(u8Vector buffer)
{
    Ebu::EbuGeneralSubtitleInformation a;
    a.CodePageNumber = getASCIIString(buffer, 0, 3);
    a.DiskFormatCode = getASCIIString(buffer, 3, 8);
    a.DisplayStandardCode = getASCIIString(buffer, 11, 1);
    a.CharacterCodeTableNumber = getASCIIString(buffer, 12, 2);
    a.LanguageCode = getASCIIString(buffer, 14, 2);
    a.OriginalProgrammeTitle = getASCIIString(buffer, 16, 32);
    a.OriginalEpisodeTitle = getASCIIString(buffer, 48, 32);
    a.TranslatedProgrammeTitle = getASCIIString(buffer, 80, 32);
    a.TranslatedEpisodeTitle = getASCIIString(buffer, 112, 32);
    a.TranslatorsName = getASCIIString(buffer, 144, 32);
    a.TranslatorsContactDetails = getASCIIString(buffer, 176, 32);
    a.SubtitleListReferenceCode = getASCIIString(buffer, 208, 16);
    a.CreationDate = getASCIIString(buffer, 224, 6);
    a.RevisionDate = getASCIIString(buffer, 230, 6);
    a.RevisionNumber = getASCIIString(buffer, 236, 2);
    a.TotalNumberOfTextAndTimingInformationBlocks = getASCIIString(buffer, 238, 5);
    a.TotalNumberOfSubtitles = getASCIIString(buffer, 243, 5);
    a.TotalNumberOfSubtitleGroups = getASCIIString(buffer, 248, 3);
    a.MaximumNumberOfDisplayableCharactersInAnyTextRow = getASCIIString(buffer, 251, 2);
    a.MaximumNumberOfDisplayableRows = getASCIIString(buffer, 253, 2);
    a.TimeCodeStatus = getASCIIString(buffer, 255, 1);
    a.TimeCodeStartOfProgramme = getASCIIString(buffer, 256, 8);
    a.CountryOfOrigin = getASCIIString(buffer, 274, 3);
    a.SpareBytes = getASCIIString(buffer, 373, 75);
    a.UserDefinedArea = getASCIIString(buffer, 448, 576);

    // printf("CodePageNumber = %s DiskFormatCode = %s\n", a.CodePageNumber.c_str(), a.DiskFormatCode.c_str());
    return a;
}



bool Ebu::probe(std::istream& istrm)
{
	u8Vector buffer = FileUtil::ReadAllStream(istrm);
	
    // printf("Ebu::probe(): %ld\n", buffer.size());

    // step 1 : file size must be not too small or too big
    if (buffer.size() < 1024 + 128 || buffer.size() > 2048000)
    {
        return false;
    }

    // step 2 : file size must be divided by 128
    if (buffer.size() % 128 != 0)
    {
        return false;
    }

    Ebu::EbuGeneralSubtitleInformation header = ReadHeader(buffer);
    if (StringHelper::startsWith(header.DiskFormatCode, "STL23") || 
        StringHelper::startsWith(header.DiskFormatCode, "STL24") ||
        StringHelper::startsWith(header.DiskFormatCode, "STL25") ||
        StringHelper::startsWith(header.DiskFormatCode, "STL29") ||
        StringHelper::startsWith(header.DiskFormatCode, "STL30") ||
        StringHelper::startsWith(header.DiskFormatCode, "STL35") ||
        StringHelper::startsWith(header.DiskFormatCode, "STL48") ||
        StringHelper::startsWith(header.DiskFormatCode, "STL50") ||
        StringHelper::startsWith(header.DiskFormatCode, "STL60"))
    {
        return true;
    }

    return false;
}

bool Ebu::IsMine(const std::string& fileName)
{	
	if (!fileName.empty()/* && FileSystem::fileExists(fileName)*/)
	{
		_finddata_t fi = getFileInfo(fileName);

		if (fi.size >= (1024 + 128) && fi.size < 2048000) // not too small or too big
		{
			if (fileName.substr(fileName.length()-4) != ".stl")
			{
				return false;
			}
        
            // read file content
            std::ifstream is(fileName);
            u8Vector buffer = FileUtil::ReadBytes(is, 0, 1024);
            Ebu::EbuGeneralSubtitleInformation header = ReadHeader(buffer);

            if (StringHelper::startsWith(header.DiskFormatCode, "STL23") || 
                StringHelper::startsWith(header.DiskFormatCode, "STL24") ||
                StringHelper::startsWith(header.DiskFormatCode, "STL25") ||
                StringHelper::startsWith(header.DiskFormatCode, "STL29") ||
                StringHelper::startsWith(header.DiskFormatCode, "STL30") ||
                StringHelper::startsWith(header.DiskFormatCode, "STL35") ||
                StringHelper::startsWith(header.DiskFormatCode, "STL48") ||
                StringHelper::startsWith(header.DiskFormatCode, "STL50") ||
                StringHelper::startsWith(header.DiskFormatCode, "STL60"))
                {
        			return SubtitleFormat::IsMine(fileName);
                }
            else 
            {
                return false;
            }

		}
	}
	return false;
}

double Ebu::GetFrameForCalculation(double frameRate)
{
    if (std::abs(frameRate - 23.976) < 0.01)
    {
        return 24000.0 / 1001.0;
    }
    if (std::abs(frameRate - 29.97) < 0.01)
    {
        return 30000.0 / 1001.0;
    }
    if (std::abs(frameRate - 59.94) < 0.01)
    {
        return 60000.0 / 1001.0;
    }

    return frameRate;
}

int Ebu::FramesToMillisecondsMax999(int frames, double currentFrameRate)
{
    int ms = (int)std::round(frames * (Ebu::BaseUnit / GetFrameForCalculation(currentFrameRate)));
    return std::min(ms, 999);
}

std::string Ebu::GetCharacter(bool &skipNext, EbuGeneralSubtitleInformation header, u8Vector buffer, int index)
{
    skipNext = false;
    if (header.LanguageCode.find(LanguageCodeChinese) != std::string::npos)
    {
        skipNext = true;
        // return Encoding.GetEncoding(1200).GetString(buffer, index, 2); // 16-bit Unicode
        return "";
    }

    if (header.CharacterCodeTableNumber.find("00") != std::string::npos)
    {
        unsigned char b = buffer[index];
        if (b == 0xd3) { return "©"; }
        else if (b == 0xd4) { return "™"; }
        else if (b == 0xd5) { return "♪"; }

        // note that 0xC1 ~ 0xCF combines characters : return its next byte for ascii
        if (index + 2 > (int)buffer.size()) { return ""; }

        //
        // HERE : Default encoding - 20269 : ISO-6937
        //

        char next = (char) buffer[index+1];
        switch(b)
        {
            case 0xc1: // Grave
            {
                std::string possibleStr = "AEIOUaeiou";
                if (possibleStr.find(next) != std::string::npos) 
                {
                    skipNext = true;
                    switch(next) 
                    {
                        case 'A': return "À";
                        case 'E': return "È";
                        case 'I': return "Ì";
                        case 'O': return "Ò";
                        case 'U': return "Ù";
                        case 'a': return "à";
                        case 'e': return "è";
                        case 'i': return "ì";
                        case 'o': return "ò";
                        case 'u': return "ù";
                    }
                }
                break;
            }
            case 0xc2: // Acute
            {
                std::string possibleStr = "ACEILNORSUYZacegilnorsuyz";
                if (possibleStr.find(next) != std::string::npos) 
                {
                    skipNext = true;
                    switch (next)
                    {
                        case 'A': return "Á";
                        case 'C': return "Ć";
                        case 'E': return "É";
                        case 'I': return "Í";
                        case 'L': return "Ĺ";
                        case 'N': return "Ń";
                        case 'O': return "Ó";
                        case 'R': return "Ŕ";
                        case 'S': return "Ś";
                        case 'U': return "Ú";
                        case 'Y': return "Ý";
                        case 'Z': return "Ź";
                        case 'a': return "á";
                        case 'c': return "ć";
                        case 'e': return "é";
                        case 'g': return "ģ";
                        case 'i': return "í";
                        case 'l': return "ĺ";
                        case 'n': return "ń";
                        case 'o': return "ó";
                        case 'r': return "ŕ";
                        case 's': return "ś";
                        case 'u': return "ú";
                        case 'y': return "ý";
                        case 'z': return "ź";
                    }
                }
                break;
            }
            case 0xc3: // Circumflex
            {
                std::string possibleStr = "ACEGHIJOSUWYaceghjosuwyıi";
                if (possibleStr.find(next) != std::string::npos) 
                {
                    skipNext = true;
                    switch (next)
                    {
                        case 'A': return "Â";
                        case 'C': return "Ĉ";
                        case 'E': return "Ê";
                        case 'G': return "Ĝ";
                        case 'H': return "Ĥ";
                        case 'I': return "Î";
                        case 'J': return "Ĵ";
                        case 'O': return "Ô";
                        case 'S': return "Ŝ";
                        case 'U': return "Û";
                        case 'W': return "Ŵ";
                        case 'Y': return "Ŷ";
                        case 'a': return "â";
                        case 'c': return "ĉ";
                        case 'e': return "ê";
                        case 'g': return "ĝ";
                        case 'h': return "ĥ";
                        case 'j': return "ĵ";
                        case 'o': return "ô";
                        case 's': return "ŝ";
                        case 'u': return "û";
                        case 'w': return "ŵ";
                        case 'y': return "ŷ";
                        // case 'ı': return "ı̂";
                        case 'i': return "î";
                    }
                }
                break;
            }
            case 0xc4: // Tilde
            {
                std::string possibleStr = "AINOUainou";
                if (possibleStr.find(next) != std::string::npos) 
                {
                    skipNext = true; 
                    switch (next)
                    {
                        case 'A': return "Ã";
                        case 'I': return "Ĩ";
                        case 'N': return "Ñ";
                        case 'O': return "Õ";
                        case 'U': return "Ũ";
                        case 'a': return "ã";
                        case 'i': return "ĩ";
                        case 'n': return "ñ";
                        case 'o': return "õ";
                        case 'u': return "ũ";
                    }
                }
                break;
            }
            case 0xc5: // Macron
            {
                std::string possibleStr = "AEIOUaeiou";
                if (possibleStr.find(next) != std::string::npos) 
                {
                    skipNext = true; 
                    switch (next)
                    {
                        case 'A': return "Ā";
                        case 'E': return "Ē";
                        case 'I': return "Ī";
                        case 'O': return "Ō";
                        case 'U': return "Ū";
                        case 'a': return "ā";
                        case 'e': return "ē";
                        case 'i': return "ī";
                        case 'o': return "ō";
                        case 'u': return "ū";
                    }
                }
                break;
            }
            case 0xc6: // Breve
            {
                std::string possibleStr = "AGUagu";
                if (possibleStr.find(next) != std::string::npos) 
                {
                    skipNext = true; 
                    switch (next)
                    {
                        case 'A': return "Ă";
                        case 'G': return "Ğ";
                        case 'U': return "Ŭ";
                        case 'a': return "ă";
                        case 'g': return "ğ";
                        case 'u': return "ŭ";
                    }
                }
                break;
            }
            case 0xc7: // Dot
            {
                std::string possibleStr = "CEGIZcegiz";
                if (possibleStr.find(next) != std::string::npos) 
                {
                    skipNext = true;
                    switch (next)
                    {
                        case 'C': return "Ċ";
                        case 'E': return "Ė";
                        case 'G': return "Ġ";
                        case 'I': return "İ";
                        case 'Z': return "Ż";
                        case 'c': return "ċ";
                        case 'e': return "ė";
                        case 'g': return "ġ";
                        case 'i': return "ı";
                        case 'z': return "ż";
                    }
                }
                break;
            }
            case 0xc8: // Umlaut or 
            {
                std::string possibleStr = "AEIOUYaeiouy";
                if (possibleStr.find(next) != std::string::npos) 
                {
                    skipNext = true;
                    switch (next)
                    {
                        case 'A': return "Ä";
                        case 'E': return "Ë";
                        case 'I': return "Ï";
                        case 'O': return "Ö";
                        case 'U': return "Ü";
                        case 'Y': return "Ÿ";
                        case 'a': return "ä";
                        case 'e': return "ë";
                        case 'i': return "ï";
                        case 'o': return "ö";
                        case 'u': return "ü";
                        case 'y': return "ÿ";
                    }
                }
                break;
            }
            case 0xca: // Ring
            {
                std::string possibleStr = "AUau";
                if (possibleStr.find(next) != std::string::npos) 
                {
                    skipNext = true; 
                    switch (next)
                    {
                        case 'A': return "Å";
                        case 'U': return "Ů";
                        case 'a': return "å";
                        case 'u': return "ů";
                    }
                }
                break;
            }
            case 0xcb: // Cedilla
            {
                std::string possibleStr = "CGKLNRSTcklnrst";
                if (possibleStr.find(next) != std::string::npos) 
                {
                    skipNext = true;
                    switch (next)
                    {
                        case 'C': return "Ç";
                        case 'G': return "Ģ";
                        case 'K': return "Ķ";
                        case 'L': return "Ļ";
                        case 'N': return "Ņ";
                        case 'R': return "Ŗ";
                        case 'S': return "Ş";
                        case 'T': return "Ţ";
                        case 'c': return "ç";
                        case 'k': return "ķ";
                        case 'l': return "ļ";
                        case 'n': return "ņ";
                        case 'r': return "ŗ";
                        case 's': return "ş";
                        case 't': return "ţ";
                    }
                }
                break;
            }
            case 0xcd: // DoubleAcute
            {
                std::string possibleStr = "OUou";
                if (possibleStr.find(next) != std::string::npos) 
                {
                    skipNext = true;
                    switch (next)
                    {
                        case 'O': return "Ő";
                        case 'U': return "Ű";
                        case 'o': return "ő";
                        case 'u': return "ű";
                    }
                }
                break;
            }
            case 0xce: // Ogonek
            {
                std::string possibleStr = "AEIUaeiu";
                if (possibleStr.find(next) != std::string::npos) 
                {
                    skipNext = true;
                    switch (next)
                    {
                        case 'A': return "Ą";
                        case 'E': return "Ę";
                        case 'I': return "Į";
                        case 'U': return "Ų";
                        case 'a': return "ą";
                        case 'e': return "ę";
                        case 'i': return "į";
                        case 'u': return "ų";
                    }
                }
                break;
            }
            case 0xcf: // Caron
            {
                std::string possibleStr = "CDELNRSTZcdelnrstz";
                if (possibleStr.find(next) != std::string::npos) 
                {
                    skipNext = true;                    
                    switch (next)
                    {
                        case 'C': return "Č";
                        case 'D': return "Ď";
                        case 'E': return "Ě";
                        case 'L': return "Ľ";
                        case 'N': return "Ň";
                        case 'R': return "Ř";
                        case 'S': return "Š";
                        case 'T': return "Ť";
                        case 'Z': return "Ž";
                        case 'c': return "č";
                        case 'd': return "ď";
                        case 'e': return "ě";
                        case 'l': return "ľ";
                        case 'n': return "ň";
                        case 'r': return "ř";
                        case 's': return "š";
                        case 't': return "ť";
                        case 'z': return "ž";
                    }
                }
                break;
            }
            default:
            {
                // Apply ISO-6937 charset
                switch ((int)b) 
                {
                    case 0x24: return "¤";
                    case 0x7f: return "";
                    case 0x9e: return "?";
                    case 0x9f: return "?";
                    case 0xa3: return "£";
                    case 0xa4: return "$";
                    case 0xa6: return "#";
                    case 0xa8: return "¤";
                    case 0xa9: return "‘";
                    case 0xaa: return "“";
                    case 0xac: return "←";
                    case 0xad: return "↑";
                    case 0xae: return "→";
                    case 0xaf: return "↓";
                    case 0xb4: return "×";
                    case 0xb8: return "÷";
                    case 0xb9: return "’";
                    case 0xba: return "”";
                    case 0xbe: return "";
                    case 0xc0: return "?";
                    case 0xc1: return "`";
                    case 0xc2: return "´";
                    case 0xc3: return "^";
                    case 0xc4: return "~";
                    case 0xc5: return "¯";
                    case 0xc6: return "̆";
                    case 0xc7: return "";
                    case 0xc8: return "̈";
                    case 0xc9: return "?";
                    case 0xca: return "";
                    case 0xcb: return "";
                    case 0xcc: return "";
                    case 0xcd: return "";
                    case 0xce: return "";
                    case 0xcf: return "";
                    case 0xd0: return "―";
                    case 0xd1: return "¹";
                    case 0xd2: return "®";
                    case 0xd3: return "©";
                    case 0xd4: return "™";
                    case 0xd5: return "♩";
                    case 0xd6: return "";
                    case 0xd7: return "";
                    case 0xd8: return "";
                    case 0xd9: return "";
                    case 0xda: return "?";
                    case 0xdb: return "?";
                    case 0xdc: return "⅛";
                    case 0xdd: return "⅜";
                    case 0xde: return "⅝";
                    case 0xdf: return "⅞";
                    case 0xe0: return "Ω";
                    case 0xe1: return "Æ";
                    case 0xe2: return "Ð";
                    case 0xe3: return "";
                    case 0xe4: return "Ħ";
                    case 0xe5: return "?";
                    case 0xe6: return "Ĳ";
                    case 0xe7: return "Ŀ";
                    case 0xe8: return "Ł";
                    case 0xe9: return "Ø";
                    case 0xea: return "Œ";
                    case 0xeb: return "º";
                    case 0xec: return "Þ";
                    case 0xed: return "Ŧ";
                    case 0xee: return "Ŋ";
                    case 0xef: return "ŉ";
                    case 0xf0: return "ĸ";
                    case 0xf1: return "æ";
                    case 0xf2: return "đ";
                    case 0xf3: return "ð";
                    case 0xf4: return "ħ";
                    case 0xf5: return "ı";
                    case 0xf6: return "ĳ";
                    case 0xf7: return "ŀ";
                    case 0xf8: return "ł";
                    case 0xf9: return "ø";
                    case 0xfa: return "œ";
                    case 0xfb: return "ß";
                    case 0xfc: return "þ";
                    case 0xfd: return "ŧ";
                    case 0xfe: return "";
                    case 0xff: return "";
                    default:
                    {
                        std::string nextStr = "";
                        nextStr.append((const char*)&b, 1);
                        return nextStr;
                    }
                }

            }
        }
    }

    if ((header.CharacterCodeTableNumber.find("01") != std::string::npos) ||
        (header.CharacterCodeTableNumber.find("02") != std::string::npos) ||
        (header.CharacterCodeTableNumber.find("03") != std::string::npos) ||
        (header.CharacterCodeTableNumber.find("04") != std::string::npos))
    {
        unsigned char b = buffer[index];
        std::string result = "";
        result.append((const char*)&b, 1);
        return result;
    }

    return "";
}

std::vector<Ebu::EbuTextTimingInformation> Ebu::ReadTextAndTiming(u8Vector buffer, Ebu::EbuGeneralSubtitleInformation header)
{
    double currentFrameRate = header.FrameRate();

    std::vector<Ebu::EbuTextTimingInformation> list;
    list.clear();

    int startOfTextAndTimingBlock = 1024;
    int ttiSize = 128;

    int index = startOfTextAndTimingBlock;
    while (index + ttiSize <= (int)buffer.size()) 
    {
        Ebu::EbuTextTimingInformation tti;
        tti.SubtitleGroupNumber = (byte)buffer[index];
        tti.SubtitleNumber = (ushort)(buffer[index + 2] * 256 + buffer[index + 1]);
        tti.ExtensionBlockNumber = (byte)buffer[index + 3];
        tti.CumulativeStatus = (byte)buffer[index + 4];
        tti.TimeCodeInHours = buffer[index + 5 + 0];
        tti.TimeCodeInMinutes = buffer[index + 5 + 1];
        tti.TimeCodeInSeconds = buffer[index + 5 + 2];

        int inFrames = (int)buffer[index + 5 + 3];
        tti.TimeCodeInMilliseconds = FramesToMillisecondsMax999(inFrames, currentFrameRate);
        tti.TimeCodeOutHours = buffer[index + 9 + 0];
        tti.TimeCodeOutMinutes = buffer[index + 9 + 1];
        tti.TimeCodeOutSeconds = buffer[index + 9 + 2];

        int outFrames = (int)buffer[index + 9 + 3];
        tti.TimeCodeOutMilliseconds = FramesToMillisecondsMax999(outFrames, currentFrameRate);
        tti.VerticalPosition = (byte)buffer[index + 13];
        tti.JustificationCode = (byte)buffer[index + 14];
        tti.CommentFlag = (byte)buffer[index + 15];

        VerticalPositions.push_back((int)tti.VerticalPosition);
        JustificationCodes.push_back((int)tti.JustificationCode);


        // Text block
        // - has a fixed length of 112 byte
        // - 8Ah = new line
        // - unused space = 8Fh
        int i = index + 16;        
        bool open = false;
        if ((header.DisplayStandardCode.find("1") == std::string::npos) &&
            (header.DisplayStandardCode.find("2") == std::string::npos)) 
        {
            open = true;
        }

        bool closed = false;
        if (header.DisplayStandardCode.find("0") == std::string::npos)
        {
            closed = true;
        }

        int max = i + 112;
        std::string sb = "";
        while (i < max) 
        {
            unsigned char b = buffer[i];
            if (b <= 0x1f) 
            {
                if (closed)
                {
                    // var tag = GetColorOrTag(b);
                    // if (!string.IsNullOrEmpty(tag))
                    // {
                    //     sb.append(tag);
                    // }
                }
            }
            else if (b >= 0x20 && b <= 0x7f) // Both - Character codes
            {
                bool skipNext = false;
                std::string value = GetCharacter(skipNext, header, buffer, i);
                sb.append(value);
                if (skipNext) i++;
            }
            else if (b >= 0x80 && b <= 0x85) // Open - italic/underline/boxing
            {
                if (open)
                {
                    // if (b == italicsOn && header.LanguageCode != LanguageCodeChinese)
                    // {
                    //     sb.Append("<i>");
                    // }
                    // else if (b == italicsOff && header.LanguageCode != LanguageCodeChinese)
                    // {
                    //     sb.Append("</i>");
                    // }
                    // else if (b == underlineOn && header.LanguageCode != LanguageCodeChinese)
                    // {
                    //     sb.Append("<u>");
                    // }
                    // else if (b == underlineOff && header.LanguageCode != LanguageCodeChinese)
                    // {
                    //     sb.Append("</u>");
                    // }
                    // else if (b == boxingOn && header.LanguageCode != LanguageCodeChinese)
                    // {
                    //     sb.Append("<box>");
                    // }
                    // else if (b == boxingOff && header.LanguageCode != LanguageCodeChinese)
                    // {
                    //     sb.Append("</box>");
                    // }
                }
            }
            else if (b >= 0x86 && b <= 0x89) // Both - Reserved for future use
            {                
            }
            else if (b == 0x8a) // Both - CR/LF
            {
                sb.append("\n");
            }
            else if (b >= 0x8b && b <= 0x8e) // Both - Reserved for future use
            {                
            }
            else if (b == 0x8f) // Both - unused space
            {                
            }
            else if (b >= 0x90 && b <= 0x9f) // Both - Reserved for future use
            {                
            }
            else if (b >= 0xa1) // Both - Character codes
            {
                bool skipNext = false;
                std::string value = GetCharacter(skipNext, header, buffer, i);
                sb.append(value);
                if (skipNext) i++;
            }
            i++;
        }

        // split lines and trim
        tti.TextField = "";
        std::vector<std::string> lines = StringHelper::split(sb, '\n');
        for (std::size_t i = 0; i < lines.size() - 1; ++i) {
            tti.TextField = tti.TextField + StringHelper::trim(lines[i]);
            tti.TextField = tti.TextField + "\\N";
        }
        tti.TextField = tti.TextField + StringHelper::trim(lines[lines.size() - 1]);

        int rows = 23;
        try {
            rows = std::stoi(header.MaximumNumberOfDisplayableRows);
        }
        catch (const std::invalid_argument & e) {
            rows = 23;
        }

        if ((int)tti.VerticalPosition < 3) 
        {
            if ((int)tti.JustificationCode == 1) // left
            {
                std::string temp = "{\\an7}";
                temp = temp + tti.TextField;
                tti.TextField = temp;
            }
            else if ((int)tti.JustificationCode == 3) // right
            {
                std::string temp = "{\\an9}";
                temp = temp + tti.TextField;
                tti.TextField = temp;
            }
            else 
            {
                std::string temp = "{\\an8}";
                temp = temp + tti.TextField;
                tti.TextField = temp;
            }
        }
        else if ((int)tti.VerticalPosition <= rows / 2 + 1)
        {
            if ((int)tti.JustificationCode == 1) // left
            {
                std::string temp = "{\\an4}";
                temp = temp + tti.TextField;
                tti.TextField = temp;
            }
            else if ((int)tti.JustificationCode == 3) // right
            {
                std::string temp = "{\\an6}";
                temp = temp + tti.TextField;
                tti.TextField = temp;
            }
            else 
            {
                std::string temp = "{\\an5}";
                temp = temp + tti.TextField;
                tti.TextField = temp;
            }
        }
        else 
        {
            if ((int)tti.JustificationCode == 1) // left
            {
                std::string temp = "{\\an1}";
                temp = temp + tti.TextField;
                tti.TextField = temp;
            }
            else if ((int)tti.JustificationCode == 3) // right
            {
                std::string temp = "{\\an3}";
                temp = temp + tti.TextField;
                tti.TextField = temp;
            }
        }

        index += ttiSize;
        list.push_back(tti);
    }

    // printf("List size = %ld\n", list.size());
    return list;
}

bool Ebu::getIsTimeBased() const
{
    return false;
}

Subtitle* Ebu::LoadSubtitle(std::istream& istrm)
{
    u8Vector buffer = FileUtil::ReadAllStream(istrm);

    Subtitle* subtitle = new Subtitle();
    subtitle->Paragraphs.clear();
    subtitle->Header.clear();

    Ebu::EbuGeneralSubtitleInformation header = ReadHeader(buffer);
    // subtitle->Header.push_back(getASCIIString(buffer, 0, 1024));

    JustificationCodes.clear();
    VerticalPositions.clear();

    Paragraph *last = NULL;
    int lastExtensionBlockNumber = 0xff;

    std::vector<Ebu::EbuTextTimingInformation> ttis = ReadTextAndTiming(buffer, header);
    for(const auto& tti: ttis) 
    {
        if (tti.ExtensionBlockNumber != (byte)0xfe) // FEh : Reserved for User data
        {
            auto p = new Paragraph();
            p->Text = tti.TextField;
			p->StartTime = new TimeCode(tti.TimeCodeInHours, tti.TimeCodeInMinutes, tti.TimeCodeInSeconds, tti.TimeCodeInMilliseconds);
			p->EndTime = new TimeCode(tti.TimeCodeOutHours, tti.TimeCodeOutMinutes, tti.TimeCodeOutSeconds, tti.TimeCodeOutMilliseconds);
            p->MarginV = std::to_string((int)tti.VerticalPosition);

            if ((std::abs(p->StartTime->getTotalMilliseconds()) < 0.01) &&
                (std::abs(p->EndTime->getTotalMilliseconds()) < 0.01)) 
            {
                p->StartTime->setTotalMilliseconds(TimeCode::MaxTimeTotalMilliseconds);
                p->EndTime->setTotalMilliseconds(TimeCode::MaxTimeTotalMilliseconds);
            }

            // printf("Timecode: %s %s : %s\n", p->StartTime->ToString().c_str(), p->EndTime->ToString().c_str(), tti.TextField.c_str());
            if (lastExtensionBlockNumber != 0xff && last != NULL)
            {
                last->Text = p->Text;   // merge text
            }
            else {
                subtitle->Paragraphs.push_back(p);
                last = p;
            }

            lastExtensionBlockNumber = (int)tti.ExtensionBlockNumber;
        }
    }

    subtitle->Renumber();
    return subtitle;
}

void Ebu::LoadSubtitle(Subtitle** subtitle, const std::string& fileName)
{
    std::ifstream is(fileName);
    *subtitle = LoadSubtitle(is);
}
