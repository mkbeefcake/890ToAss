#pragma once

#include "../libse/Subtitle.h"
#include <string>
#include <vector>
#include <cmath>
#include "../../common/bankersrounding.h"

class SubtitleFormat
{
private:
	bool BatchMode = false;

protected:
	static std::vector<char> SplitCharColon;

	int _errorCount = 0;

public:
	virtual std::string getExtension() const = 0;

	virtual std::string getName() const = 0;

	virtual bool getIsTimeBased() const;

	virtual bool IsMine(const std::string &fileName);

	virtual std::string ToText(Subtitle *subtitle, const std::string &title) = 0;

	virtual void LoadSubtitle(Subtitle **subtitle,  const std::string &fileName) = 0;

	static double GetFrameForCalculation(double frameRate);

	static int MillisecondsToFramesMaxFrameRate(double milliseconds);

	bool getBatchMode() const;
	void setBatchMode(bool value);

	static std::vector<SubtitleFormat*> GetBinaryFormats(bool batchMode);

};
