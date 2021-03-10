#include "PacUnicode.h"
#include "Pac.h"
#include "../libse/FileUtil.h"
#include "../libse/Paragraph.h"
#include "../libse/StringExtensions.h"
#include "../../my_api.h"
#include <fstream>
std::string PacUnicode::getExtension() const
{
	return ".fpc";
}

std::string PacUnicode::getName() const
{
	return "PAC Unicode (UniPac)";
}

bool PacUnicode::IsMine(const std::string &fileName)
{
	//if (!fileName.empty() && FileSystem::fileExists(fileName))
		
	if (!fileName.empty())
	{
		try
		{
			//auto fi = new FileInfo(fileName);
			_finddata_t fi = getFileInfo(fileName);
			
			//if (fi->Length > 100 && fi->Length < 1024000) // not too small or too big
			if (fi.size > 100 && fi.size < 1024000) // not too small or too big
			{
				u8Vector buffer = FileUtil::ReadAllBytesShared(fileName);

				if (buffer[00] == 1 && buffer[01] == 0 && buffer[02] == 0 && buffer[03] == 0 && buffer[04] == 0 && buffer[05] == 0 && buffer[06] == 0 && buffer[07] == 0 && buffer[8] == 0 && buffer[9] == 0 && buffer[10] == 0 && buffer[11] == 0 && buffer[12] == 0 && buffer[13] == 0 && buffer[14] == 0 && buffer[15] == 0 && buffer[16] == 0 && buffer[17] == 0 && buffer[18] == 0 && buffer[19] == 0 && buffer[20] == 0 && StringHelper::endsWith(StringHelper::toLower(fileName), ".fpc"))
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

std::string PacUnicode::ToText(Subtitle *subtitle, const std::string &title)
{
	// to avoid -Wunused-parameter
	UNUSED(subtitle);
	UNUSED(title);

	return "Not supported!";
}

Subtitle* PacUnicode::LoadSubtitle(std::istream& isrm)
{
    u8Vector buffer = FileUtil::ReadAllStream(isrm);
    Subtitle* subtitle = new Subtitle();

    subtitle->Paragraphs.clear();
    subtitle->Header.clear();


    int index = 0;
    while (index < (int) buffer.size())
    {
        Paragraph *p = PacUnicode::GetPacParagraph(index, buffer);
        if (p != nullptr)
        {
            subtitle->Paragraphs.push_back(p);
        }
    }
    if (subtitle->Paragraphs.size() > 2 && subtitle->Paragraphs[0]->StartTime->getTotalMilliseconds() < 0.001 && subtitle->Paragraphs[0]->EndTime->getTotalMilliseconds() < 0.001)
    {
        subtitle->Paragraphs.erase(subtitle->Paragraphs.begin());
    }

    subtitle->Renumber();

    return subtitle;
}

void PacUnicode::LoadSubtitle(Subtitle **subtitle, const std::string &fileName)
{
    std::ifstream is(fileName);
    *subtitle = LoadSubtitle(is);
}


void PacUnicode::ProcessLastPart(Paragraph*& p, unsigned char verticalAlignment, unsigned char alignment)
{
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

	// Remove all control-characters if any in p.Text.
	p->Text = StringExtensions::RemoveControlCharactersButWhiteSpace(p->Text);


	p->Text = StringHelper::replace(p->Text, std::string("\r\n") + " ", "\r\n");
	p->Text = StringHelper::replace(p->Text, std::string("\r\n") + " ", "\r\n");
	p->Text = StringHelper::replace(p->Text, std::string("\r\n") + " ", "\r\n");

	// Fix italics (basic)
	if (StringExtensions::StartsWith(p->Text, '<') && !StringHelper::startsWith(StringHelper::toLower(p->Text), "<i>") && !StringHelper::startsWith(StringHelper::toLower(p->Text), "<b>") && !StringHelper::startsWith(StringHelper::toLower(p->Text), "<u>") && !StringHelper::startsWith(StringHelper::toLower(p->Text), "<font "))
	{
		p->Text = "<i>" + StringHelper::replace(StringHelper::trimStart(p->Text, "<"), std::string("\r\n") + "<", "\r\n") + "</i>";
	}
	else if (p->Text.find(std::string("\r\n") + "<"))
	{
		p->Text = StringHelper::replace(p->Text, std::string("\r\n") + "<", std::string("\r\n") + "<i>") + "</i>";
	}
}


Paragraph* PacUnicode::GetPacParagraph(int& index, u8Vector& buffer)
{
	while (index < 15)
	{
		index++;
	}
	bool con = true;
	while (con)
	{
		index++;
		if (index + 20 >= (int) buffer.size())
		{
			return nullptr;
		}

		if (buffer[index] == 0xFE && buffer[index - 1] == 0x80)
		{
			con = false;
		}
	}

	int feIndex = index;
	unsigned char alignment = buffer[feIndex + 1];
	unsigned char verticalAlignment = buffer[feIndex - 1];
	auto p = new Paragraph();

	int timeStartIndex = feIndex - 15;
	p->StartTime = Pac::GetTimeCode(timeStartIndex + 1, buffer);
	p->EndTime = Pac::GetTimeCode(timeStartIndex + 5, buffer);

	int textLength = buffer[timeStartIndex + 9] + buffer[timeStartIndex + 10] * 256;
	if (textLength > 500)
	{
		delete p;
		return nullptr; // probably not correct index
	}

	int maxIndex = timeStartIndex + 10 + textLength;

	auto sb = new StringBuilder();
	index = feIndex + 3;

	int textIndex = index;
	int textBegin = index;
	while (textIndex < (int) buffer.size() && textIndex <= maxIndex)
	{
		if (buffer[textIndex] == 0xFE)
		{
			if (textIndex > textBegin)
			{
				for (int j = textBegin; j <= textIndex - textBegin - 1; j++)
				{
					if (buffer[j] == 0xff)
					{
						buffer[j] = 0x2e; // replace end of line marker
					}
				}

				sb->appendLine(getUTF8String(buffer, textBegin, textIndex - textBegin));
				textBegin = textIndex + 7;
				textIndex += 6;
			}
		}
		else if (buffer[textIndex] == 0xFF)
		{
			sb->append(' ');
		}
		textIndex++;
	}

	if (textIndex > textBegin)
	{
		sb->append(getUTF8String(buffer, textBegin, textIndex - textBegin - 1));
	}

	p->Text = StringHelper::trim(sb->toString());
	if (p->Text.length() > 1 && (p->Text.at(0) == 31 || (p->Text.at(0) == '\xFF' && p->Text.at(1) == '\xFE') )) //p->Text[1] == 65279
	{
		p->Text.erase(0, 2);
	}

	for (int k = 0; k < (int) p->Text.length(); k++)
	{
		// if (p->Text[k] == 65533)
		if ((k < (int) p->Text.length() - 1) && (p->Text.at(k) == '\xFD' && p->Text.at(k+1) == '\xFF'))
		{
			//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the .NET String 'Insert' method unless assigning to the string instance:
			p->Text.erase(k, 1).insert(k, ".");
		}
	}

	index += textLength;
	if (index + 20 >= (int) buffer.size())
	{
		delete sb;
		delete p;
		return nullptr;
	}

	p->Text = StringHelper::replace(p->Text, std::string("\r\n") + " ", "\r\n");
	p->Text = StringHelper::replace(p->Text, std::string("\r\n") + " ", "\r\n");
	p->Text = StringHelper::replace(p->Text, std::string("\r\n") + ">", "\r\n");
	p->Text = StringHelper::replace(p->Text, std::string("\0"), "");

	PacUnicode::ProcessLastPart(p, verticalAlignment, alignment);

	delete sb;
	//C# TO C++ CONVERTER TODO TASK: A 'delete p' statement was not added since p was passed to a method or constructor. Handle memory management manually.
	return p;
}
