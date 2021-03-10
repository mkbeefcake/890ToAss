#pragma once

#include "TimeCode.h"
#include <string>
#include "../../common/stringhelper.h"

class Paragraph
{
public:
	int Number = 0;

	std::string Text;

	TimeCode *StartTime;

	TimeCode *EndTime;

	virtual ~Paragraph()
	{
		delete StartTime;
		delete EndTime;
	}

	TimeCode *getDuration() const;

	bool Forced = false;

	std::string Extra;

	bool IsComment = false;

	std::string Actor;
	std::string Region;

	std::string MarginL;
	std::string MarginR;
	std::string MarginV;

	std::string Effect;

	int Layer = 0;

	std::string Id;

	std::string Language;

	std::string Style;

	bool NewSection = false;

	std::string Bookmark;

private:
	static std::string GenerateId();

public:
	Paragraph();

	Paragraph(TimeCode *startTime, TimeCode *endTime, const std::string &text);

	Paragraph(Paragraph *paragraph, bool generateNewId = true);

	std::string ToString();

};
