#include "Subtitle.h"
#include "StringExtensions.h"
#include "../libse/Paragraph.h"

std::string Subtitle::getFooter() const
{
	return Footer;
}

void Subtitle::setFooter(const std::string &value)
{
	Footer = value;
}

std::string Subtitle::getFileName() const
{
	return FileName;
}

void Subtitle::setFileName(const std::string &value)
{
	FileName = value;
}

Subtitle::Subtitle()
{
	//setParagraphs(ParagraphVector());
	//HistoryItems = new List<HistoryItem>();
	setFileName("Untitled");
}

Subtitle::Subtitle(Subtitle *subtitle, bool generateNewId) : Subtitle()
{
	if (subtitle == nullptr)
	{
		return;
	}

	for (auto p : subtitle->Paragraphs)
	{
		Paragraph tempVar(p, generateNewId);
		Paragraphs.push_back(&tempVar);
	}
	this->Header = subtitle->Header;
	setFooter(subtitle->getFooter());
	setFileName(subtitle->getFileName());
}

std::string Subtitle::GetAllTexts(int stopAfterBytes)
{
	int max = Paragraphs.size();
	constexpr int averageLength = 40;
	auto sb = new StringBuilder(max * averageLength);
	for (auto index = 0; index < max; index++)
	{
		sb->appendLine(Paragraphs[index]->Text);
		if ((int)sb->length() > stopAfterBytes)
		{
			delete sb;
			return sb->toString();
		}
	}

//C# TO C++ CONVERTER TODO TASK: A 'delete sb' statement was not added since sb was used in a 'return' or 'throw' statement.
	return sb->toString();
}

void Subtitle::Renumber(int startNumber)
{
	auto number = startNumber;
	int l = Paragraphs.size() + number;
	while (number < l)
	{
		auto p = Paragraphs[number - startNumber];
		p->Number = number++;
	}
}

int Subtitle::RemoveEmptyLines()
{
	int count = Paragraphs.size();
	if (count <= 0)
	{
		return 0;
	}

	int firstNumber = Paragraphs[0]->Number;
	for (int i = Paragraphs.size() - 1; i >= 0; i--)
	{
		auto p = Paragraphs[i];
		if (StringExtensions::IsOnlyControlCharactersOrWhiteSpace(p->Text))
		{
			Paragraphs.erase(Paragraphs.begin() + i);
		}
	}
	if (count != (int)Paragraphs.size())
	{
		Renumber(firstNumber);
	}
	return count - Paragraphs.size();
}
