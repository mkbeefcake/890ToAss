#include "SubtitleFormat.h"
#include "../libse/TimeCode.h"
#include "../libse/Configuration.h"
#include "Pac.h"
#include "Cavena890.h"
#include "PacUnicode.h"


std::vector<char> SubtitleFormat::SplitCharColon = {':'};

bool SubtitleFormat::getIsTimeBased() const
{
	return true;
}

bool SubtitleFormat::IsMine(const std::string &fileName)
{
	Subtitle* subtitle;// = new Subtitle();
	auto oldFrameRate = Configuration::getSettings()->General->getCurrentFrameRate();
	LoadSubtitle(&subtitle, fileName);
	Configuration::getSettings()->General->setCurrentFrameRate(oldFrameRate);

//C# TO C++ CONVERTER TODO TASK: A 'delete subtitle' statement was not added since subtitle was passed to a method or constructor. Handle memory management manually.
	return (int) subtitle->Paragraphs.size() > _errorCount;
}

double SubtitleFormat::GetFrameForCalculation(double frameRate)
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

int SubtitleFormat::MillisecondsToFramesMaxFrameRate(double milliseconds)
{
	int frames = static_cast<int>(BankersRounding::round(milliseconds / (TimeCode::BaseUnit / GetFrameForCalculation(Configuration::getSettings()->General->getCurrentFrameRate()))));
	if (frames >= Configuration::getSettings()->General->getCurrentFrameRate())
	{
		frames = static_cast<int>(Configuration::getSettings()->General->getCurrentFrameRate() - 0.01);
	}

	return frames;
}

bool SubtitleFormat::getBatchMode() const
{
	return BatchMode;
}

void SubtitleFormat::setBatchMode(bool value)
{
	BatchMode = value;
}

std::vector<SubtitleFormat*> SubtitleFormat::GetBinaryFormats(bool batchMode)
{
	Pac *tempPac = new Pac();
	tempPac->setBatchMode(batchMode);
	
	Cavena890* tempCavena = new Cavena890();
	tempCavena->setBatchMode(batchMode);

	return std::vector<SubtitleFormat*> {tempPac, new PacUnicode(), tempCavena, new Cavena890()};
}
