#include "Paragraph.h"

TimeCode *Paragraph::getDuration() const
{
	return new TimeCode(EndTime->getTotalMilliseconds() - StartTime->getTotalMilliseconds());
}

std::string Paragraph::GenerateId()
{
	//return static_cast<std::string>(Guid::NewGuid());
	return "";
}

Paragraph::Paragraph()
{
	
	StartTime = new TimeCode();
	EndTime =  new TimeCode();
	Text = "";
	Id = GenerateId();

	MarginL = "0";
	MarginR = "0";
	MarginV = "0";
}

Paragraph::Paragraph(TimeCode *startTime, TimeCode *endTime, const std::string &text)
{
	StartTime = startTime;
	EndTime = endTime;
	Text = text;
	Id = GenerateId();
}

Paragraph::Paragraph(Paragraph *paragraph, bool generateNewId)
{
	Number = paragraph->Number;
	Text = paragraph->Text;
	StartTime = new TimeCode(paragraph->StartTime->getTotalMilliseconds());
	EndTime = new TimeCode(paragraph->EndTime->getTotalMilliseconds());
	Forced = paragraph->Forced;
	Extra = paragraph->Extra;
	IsComment = paragraph->IsComment;
	Actor = paragraph->Actor;
	Region = paragraph->Region;
	MarginL = paragraph->MarginL;
	MarginR = paragraph->MarginR;
	MarginV = paragraph->MarginV;
	Effect = paragraph->Effect;
	Layer = paragraph->Layer;
	Id = generateNewId ? GenerateId() : paragraph->Id;
	Language = paragraph->Language;
	Style = paragraph->Style;
	NewSection = paragraph->NewSection;
	Bookmark = paragraph->Bookmark;
}

std::string Paragraph::ToString()
{
	return StringHelper::formatSimple("{0} --> {1} {2}", StartTime, EndTime, Text);
}
