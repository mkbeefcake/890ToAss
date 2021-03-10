#pragma once

#include "SubtitleFormat.h"
#include "../libse/Subtitle.h"
#include <string>
#include <vector>
//#include "../tangible_filesystem.h"

/// <summary>
/// UniPac
/// </summary>
class PacUnicode : public SubtitleFormat
{
public:
	std::string getExtension() const override;

	std::string getName() const override;

	bool IsMine(const std::string &fileName) override;

	std::string ToText(Subtitle *subtitle, const std::string &title) override;
    Subtitle* LoadSubtitle(std::istream& isrm);
	void LoadSubtitle(Subtitle **subtitle, const std::string &fileName) override;

	static void ProcessLastPart(Paragraph*& p, unsigned char verticalAlignment, unsigned char alignment);
	static Paragraph* GetPacParagraph(int& index, u8Vector& buffer);
};
