#include "my_api.h"

#include "common/define.h"
#include "cavena_reader/Formats/SubtitleFormat.h"
#include "cavena_reader/libse/StringExtensions.h"
#include "cavena_reader/libse/Paragraph.h"
#include "cavena_reader/libse/Configuration.h"
#include <string.h>
#include <fstream>
_finddata_t getFileInfo(std::string file_name)
{
	struct _finddata_t c_file;
	memset(&c_file, 0, sizeof(_finddata_t));
	intptr_t hFile;
	if ((hFile = _findfirst((char*)(file_name.data()), &c_file)) != -1L)
	{
		_findclose(hFile);
	}
	return c_file;
}

bool setCodePage(int code_page) 
{
#ifdef WIN32
	char str_code_page[20] = { 0 };
	sprintf_s(str_code_page, 20, ".%d", code_page);
	//_setlocale(LC_ALL, str_code_page);
	if (_setmbcp(_MB_CP_SBCS) == -1)
	{
		printf("The fuction _setmbcp(_MB_CP_SBCS) failed!");
		return false;
	}
#endif
	// to avoid -Wunused-parameter
	UNUSED(code_page);
	return true;
}

std::string getEncodedString(u8Vector& buffer, int start, int textLength)
{
	if (start == -1)
	{
		start = 0;
		textLength = buffer.size();
	}
	return std::string(&buffer[start], &buffer[start] + textLength);
/*	char str_tmp[10000];

	mbstate_t   state = { 0 };
	size_t      nConvResult, nmbLen = 0, nwcLen = 0;
	
	char* wcCur = str_tmp;
	char* wcEnd = wcCur + textLength;

	const char* mbCur = (char*)&buffer[start];
	const char* mbEnd = mbCur + textLength;

	while ((mbCur < mbEnd) && (wcCur < wcEnd))
	{
		nConvResult = mbrtowc(wcCur, mbCur, 1, &state);
		
		switch (nConvResult)
		{
		case 0:
		{  // done
			printf("Conversion succeeded!\nMultibyte String: ");
			mbCur = mbEnd;
			break;
		}

		case -1:
		{  // encoding error
			printf("The call to mbrtowc has detected an encoding error.\n");
			mbCur = mbEnd;
			break;
		}

		case -2:
		{  // incomplete character
			if (!mbsinit(&state))
			{
				printf("Currently in middle of mb conversion, state = %x\n", *((int*)&state));
				// state will contain data regarding lead byte of mb character
			}

			++nmbLen;
			++mbCur;
			break;
		}

		default:
		{
			if (nConvResult > 2) // The multibyte should never be larger than 2
			{
				printf("Error: The size of the converted multibyte is %d.\n", nConvResult);
			}

			++nmbLen;
			++mbCur; 
			if(*wcCur != 0)
			{
				++nwcLen;
				++wcCur;
			}
			break;
		}
		}
	}
	str_tmp[nwcLen++] = 0;

	return str_tmp;*/
}


std::string getEncodedString(u8Vector& buffer)
{
	return getEncodedString(buffer, -1, -1);
}

std::string getEncodedString(u8Vector buffer)
{
	return getEncodedString(buffer, -1, -1);
}

std::string getEncodedString(int code_page, u8Vector& buffer, int start, int textLength)
{
	setCodePage(code_page);
	return getEncodedString(buffer, start, textLength);
}


std::string getASCIIString(u8Vector& buffer, int start , int textLength )
{
	setCodePage(20127);
	return getEncodedString(buffer, start, textLength);
}

std::string getUTF8String(u8Vector& buffer, int start, int textLength )
{
	setCodePage(65001);
	return getEncodedString(buffer, start, textLength);
}
void validateSubtitle(Subtitle* _subtitle)
{
    _subtitle->RemoveEmptyLines();
    for(auto p: _subtitle->Paragraphs)

    {
        // Replace U+0456 (CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I) by U+0069 (LATIN SMALL LETTER I)
        p->Text = StringHelper::replace(StringHelper::replace(p->Text, "<і>", "<i>"), "</і>", "</i>");

        // remove control characters (e.g. binary zero)
        p->Text = StringExtensions::RemoveControlCharactersButWhiteSpace(p->Text);
    }
    bool bTitleFind = false;
    for(auto header:_subtitle->Header)
    {
        if (StringHelper::startsWith(StringHelper::toUpper(header), "TITLE:"))
        {
            bTitleFind = true;
            break;
        }
    }
    if(bTitleFind == false)
    {
        std::string new_title;
//        _finddata_t fi = getFileInfo(filePath);
//        std::string file_name = fi.name;
//        new_title = file_name.substr(0, file_name.length() - 4);
        _subtitle->Header.insert(_subtitle->Header.begin(), "Title: Unknown");
    }
}
Subtitle* read_file(std::string filePath)
{
	setCodePage(1252);

	Subtitle* _subtitle;// = new Subtitle();
	bool bLoaded = false;
	
	std::vector<SubtitleFormat*> format_vec = SubtitleFormat::GetBinaryFormats(false);
	for (int i = 0; i < (int) format_vec.size();i ++)
	{
		if (format_vec[i]->IsMine(filePath))
		{
			format_vec[i]->LoadSubtitle(&_subtitle, filePath);
			bLoaded = true;
			break;
		}
	}

	if(bLoaded)
	{
        validateSubtitle(_subtitle);
		return _subtitle;
	}
	return nullptr;
}

void write_ass_info(Subtitle* subtitle, std::ostream& ostrm)
{
    ostrm<<"[Script Info]\n";
	ostrm<<"; This is an Advanced Sub Station Alpha v4+ script.\n";

	for(auto p:subtitle->Header)
	{
		ostrm<<StringHelper::replace(p, "\r\n", "\n").data()<<endl;
	}
	ostrm<<"ScriptType: v4.00+\n";
	ostrm<<"Collisions: Normal\n";
	ostrm<<"PlayDepth: 0\n\n";
}

void write_ass_styles(Subtitle* subtitle, std::ostream& ostrm)
{
	ostrm<<"[V4+ Styles]\n";
	ostrm<<"Format: Name, Fontname, Fontsize, PrimaryColour, SecondaryColour, OutlineColour, BackColour, Bold, Italic, Underline, StrikeOut, ScaleX, ScaleY, Spacing, Angle, BorderStyle, Outline, Shadow, Alignment, MarginL, MarginR, MarginV, Encoding\n";
	ostrm<<"Style: Default,Arial,20,&H00FFFFFF,&H0300FFFF,&H00000000,&H02000000,0,0,0,0,100,100,0,0,1,2,1,2,10,10,10,1\n\n";

	// to avoid -Wunused-parameter
	UNUSED(subtitle);
}

void write_ass_events(Subtitle* subtitle, std::ostream& ostrm)
{
	ostrm<<"[Events]\n";
	ostrm<<"Format: Layer, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text\n";
	std::string tmp_str;
	int i = 0;
	for (auto p : subtitle->Paragraphs)
	{
		i++;
		ostrm<<"Dialogue: 0";

		tmp_str = p->StartTime->ToASSString();
		ostrm<<","<<tmp_str;
		tmp_str = p->EndTime->ToASSString();
		ostrm<<","<<tmp_str.data();
		// ostrm<<",Default,,0,0,0,,";
		ostrm << ",Default,,";
		ostrm << p->MarginL;
		ostrm << ",";
		ostrm << p->MarginR;
		ostrm << ",";
		ostrm << p->MarginV;
		ostrm << ",,";
		ostrm<< StringHelper::replace(p->Text, "\r\n", "\\N").data()<<"\n";
	}
}

void write_to_ass(Subtitle *subtitle, char* file_name)
{
	FILE* fp;
#ifdef WIN32
	fopen_s(&fp, file_name, "w");
#else
	fp = fopen(file_name, "w");
#endif
	if (!fp) return;
	std::ofstream os(file_name);
	
	write_buffer(subtitle, os);
	fclose(fp);
}
#include "./cavena_reader/Formats/Cavena890.h"
#include "./cavena_reader/Formats/Pac.h"
#include "./cavena_reader/Formats/PacUnicode.h"
#include "./cavena_reader/Formats/Ebu.h"

bool probe_format(std::istream& istrm, int type)
{
	if (type == STREAM_TYPE_890)
	{
		Cavena890* tempCavena = new Cavena890();
		return tempCavena->probe(istrm);
	}
	if (type == STREAM_TYPE_EBU)
	{
		Ebu* tempEBU = new Ebu();
		return tempEBU->probe(istrm);
	}

	return false;
}

Subtitle* read_buffer(std::istream& istrm ,int type)
{
    Subtitle* subtitle = 0;
    if(type == STREAM_TYPE_890)
    {
        Cavena890* tempCavena = new Cavena890();
        tempCavena->setBatchMode(false);
        
        subtitle = tempCavena->LoadSubtitle(istrm);
    }
    else if(type == STREAM_TYPE_PAC)
    {
        Pac* tmp = new Pac();
        tmp->setBatchMode(false);

        subtitle = tmp->LoadSubtitle(istrm);
    }
	else if (type == STREAM_TYPE_EBU)
	{
		Ebu* tempEbu = new Ebu();
		subtitle = tempEbu->LoadSubtitle(istrm);
	}

    if(subtitle)
    {
        validateSubtitle(subtitle);
    }
    return subtitle;
}

void set_frame_rate(double frame_rate) {
    Configuration::getSettings()->General->setCurrentFrameRate(frame_rate);
}

void write_buffer(Subtitle* subtitle, std::ostream& ostrm)
{
    write_ass_info(subtitle, ostrm);
    write_ass_styles(subtitle, ostrm);
    write_ass_events(subtitle, ostrm);
}