#include "TimeCode.h"
#include "Configuration.h"
#include "../Formats/SubtitleFormat.h"
#include "StringExtensions.h"
std::vector<char> TimeCode::TimeSplitChars = {':', ',', '.'};

bool TimeCode::getIsMaxTime() const
{
	return std::abs(_totalMilliseconds - MaxTimeTotalMilliseconds) < 0.01;
}

TimeCode::TimeCode(double totalMilliseconds)
{
	_totalMilliseconds = totalMilliseconds;
}

TimeCode::TimeCode()
{
}

TimeCode::TimeCode(int hours, int minutes, int seconds, int milliseconds)
{
	_totalMilliseconds = hours * 60 * 60 * BaseUnit + minutes * 60 * BaseUnit + seconds * BaseUnit + milliseconds;
}

double TimeCode::getTotalSeconds() const
{
	return _totalMilliseconds / BaseUnit;
}

void TimeCode::setTotalSeconds(double value)
{
	_totalMilliseconds = value * BaseUnit;
}

double TimeCode::getTotalMilliseconds() const
{
	return _totalMilliseconds;
}

void TimeCode::setTotalMilliseconds(double value)
{
	_totalMilliseconds = value;
}

TimeSpan TimeCode::getTimeSpan() const
{
	return TimeSpan::FromMilliseconds(_totalMilliseconds);
}

void TimeCode::setTimeSpan(TimeSpan value)
{
	_totalMilliseconds = value.TotalMilliseconds;
}

std::string TimeCode::ToString()
{
	return ToString(false);
}

std::string TimeCode::ToString(bool localize)
{
	auto ts = getTimeSpan();
/*	std::string decimalSeparator = localize ? CultureInfo::CurrentCulture->NumberFormat->NumberDecimalSeparator : ",";
	std::string s = std::string::Format("{0:00}:{1:00}:{2:00}{3}{4:000}", ts.Hours + ts.Days * 24, ts.Minutes, ts.Seconds, decimalSeparator, ts.Milliseconds);
*/
	std::string decimalSeparator = localize ? "." : ",";

	char tmp_str[20];
#ifdef WIN32
	sprintf_s(tmp_str, 20, "%02d:%02d:%02d%s%03d", ts.Hours + ts.Days * 24, ts.Minutes, ts.Seconds, decimalSeparator.data(), ts.Milliseconds);
#else
	sprintf(tmp_str, "%02d:%02d:%02d%s%03d", ts.Hours + ts.Days * 24, ts.Minutes, ts.Seconds, decimalSeparator.data(), ts.Milliseconds);
#endif
	std::string s = tmp_str;
	return PrefixSign(s);
}

std::string TimeCode::ToDisplayString()
{
	if (getIsMaxTime())
	{
		return "-";
	}

	if (Configuration::getSettings()->General->getUseTimeFormatHHMMSSFF() == true)
	{
		return ToHHMMSSFF();
	}

	return ToString(true);
}

std::string TimeCode::ToASSString()
{
	std::string s;
	auto ts = getTimeSpan();

	char tmp_str[20];


#ifdef WIN32
	sprintf_s(tmp_str, 20, "%02d:%02d:%02d.%02d", ts.Days * 24 + ts.Hours, ts.Minutes, ts.Seconds, ts.Milliseconds / 10);
#else
	sprintf(tmp_str, "%d:%02d:%02d.%02d", ts.Days * 24 + ts.Hours, ts.Minutes, ts.Seconds, ts.Milliseconds / 10);
#endif
	s = tmp_str;

	return PrefixSign(s);
}

std::string TimeCode::ToHHMMSSFF()
{
	std::string s;
	auto ts = getTimeSpan();
	auto frames = BankersRounding::round(ts.Milliseconds / (BaseUnit / Configuration::getSettings()->General->getCurrentFrameRate()));

	char tmp_str[20];

	if (frames >= Configuration::getSettings()->General->getCurrentFrameRate() - 0.001)
	{
		auto newTs = TimeSpan(ts.Ticks);
		TimeSpan deltaSpan = TimeSpan(0, 0, 1);
		newTs = newTs.Add(deltaSpan);
//		s = std::string::Format("{0:00}:{1:00}:{2:00}:{3:00}", newTs.Days * 24 + newTs.Hours, newTs.Minutes, newTs.Seconds, 0);
#ifdef WIN32
		sprintf_s(tmp_str, 20, "%02d:%02d:%02d:%02d", newTs.Days * 24 + newTs.Hours, newTs.Minutes, newTs.Seconds, 0);
#else
		sprintf(tmp_str, "%02d:%02d:%02d:%02d", newTs.Days * 24 + newTs.Hours, newTs.Minutes, newTs.Seconds, 0);

#endif


		s = tmp_str;
	}
	else
	{
		//s = std::string::Format("{0:00}:{1:00}:{2:00}:{3:00}", ts.Days * 24 + ts.Hours, ts.Minutes, ts.Seconds, SubtitleFormat::MillisecondsToFramesMaxFrameRate(ts.Milliseconds));
#ifdef WIN32
		sprintf_s(tmp_str, 20, "%02d:%02d:%02d:%02d", ts.Days * 24 + ts.Hours, ts.Minutes, ts.Seconds, SubtitleFormat::MillisecondsToFramesMaxFrameRate(ts.Milliseconds));
#else
		sprintf(tmp_str, "%02d:%02d:%02d:%02d", ts.Days * 24 + ts.Hours, ts.Minutes, ts.Seconds, SubtitleFormat::MillisecondsToFramesMaxFrameRate(ts.Milliseconds));
#endif
		s = tmp_str;
	}
	return PrefixSign(s);
}

std::string TimeCode::ToShortDisplayString()
{
	if (getIsMaxTime())
	{
		return "-";
	}

	if (Configuration::getSettings()->General->getUseTimeFormatHHMMSSFF() == true)
	{
		return ToShortStringHHMMSSFF();
	}

	return ToShortString(true);
}

std::string TimeCode::ToShortStringHHMMSSFF()
{
	std::string s = ToHHMMSSFF();
	std::string pre = "";
	if (StringExtensions::StartsWith(s, '-'))
	{
		pre = "-";
		s = StringHelper::trimStart(s, "-");
	}
	int j = 0;
	int len = s.length();
	while (j + 6 < len && s[j] == '0' && s[j + 1] == '0' && s[j + 2] == ':')
	{
		j += 3;
	}
	s = j > 0 ? s.substr(j) : s;
	return pre + s;
}

std::string TimeCode::ToShortString(bool localize)
{
	auto ts = getTimeSpan();
	std::string decimalSeparator = localize ? "." : ",";// localize ? CultureInfo::CurrentCulture->NumberFormat->NumberDecimalSeparator : ",";
	std::string s;
	char tmp_str[20];
	if (ts.Minutes == 0 && ts.Hours == 0 && ts.Days == 0)
	{
		//s = std::string::Format("{0:0}{1}{2:000}", ts.Seconds, decimalSeparator, ts.Milliseconds);
#ifdef WIN32
		sprintf_s(tmp_str, 20, "%01d%s%03d", ts.Seconds, decimalSeparator.data(), ts.Milliseconds);
#else
		sprintf(tmp_str, "%01d%s%03d", ts.Seconds, decimalSeparator.data(), ts.Milliseconds);
#endif
		s = tmp_str;
	}
	else if (ts.Hours == 0 && ts.Days == 0)
	{
		//s = std::string::Format("{0:0}:{1:00}{2}{3:000}", ts.Minutes, ts.Seconds, decimalSeparator, ts.Milliseconds);

#ifdef WIN32
		sprintf_s(tmp_str, 20, "%01d:%02d%s%03d", ts.Minutes, ts.Seconds, decimalSeparator.data(), ts.Milliseconds);
#else
		sprintf(tmp_str, "%01d:%02d%s%03d", ts.Minutes, ts.Seconds, decimalSeparator.data(), ts.Milliseconds);
#endif
		s = tmp_str;
	}
	else
	{
		//s = std::string::Format("{0:0}:{1:00}:{2:00}{3}{4:000}", ts.Hours + ts.Days * 24, ts.Minutes, ts.Seconds, decimalSeparator, ts.Milliseconds);
#ifdef WIN32
		sprintf_s(tmp_str, 20, "%01d:%02d:%02d:%s%03d", ts.Hours + ts.Days * 24, ts.Minutes, ts.Seconds, decimalSeparator.data(), ts.Milliseconds);
#else
		sprintf(tmp_str, "%01d:%02d:%02d:%s%03d", ts.Hours + ts.Days * 24, ts.Minutes, ts.Seconds, decimalSeparator.data(), ts.Milliseconds);
#endif
		s = tmp_str;
	}
	return PrefixSign(s);
}

std::string TimeCode::PrefixSign(const std::string &time)
{
	return getTotalMilliseconds() >= 0 ? time : StringHelper::formatSimple("-{0}", StringExtensions::RemoveChar(time, '-'));
}
