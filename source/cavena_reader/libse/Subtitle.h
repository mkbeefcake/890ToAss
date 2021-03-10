#pragma once

#include "../../common/define.h"

class Subtitle
{
private:
	
	std::string Footer;
	std::string FileName;

public:
	static constexpr int MaxFileSize = 1024 * 1024 * 20; // 20 MB

	std::vector<Paragraph*>  Paragraphs;
	
	std::vector<std::string> Header;

	std::string getFooter() const;
	void setFooter(const std::string &value);

	std::string getFileName() const;
	void setFileName(const std::string &value);

	Subtitle();
	explicit Subtitle(Subtitle *subtitle, bool generateNewId = true);

	std::string GetAllTexts(int stopAfterBytes);

	void Renumber(int startNumber = 1);

	int RemoveEmptyLines();
};
