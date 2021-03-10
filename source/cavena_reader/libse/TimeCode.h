#pragma once

#include <string>
#include <vector>
#include <cmath>
#include "../../common/stringhelper.h"
#include "../../common/bankersrounding.h"
#include "TimeSpan.h"
class TimeCode
{
private:
	static std::vector<char> TimeSplitChars;
public:
	static constexpr double BaseUnit = 1000.0; // Base unit of time
private:
	double _totalMilliseconds = 0;

public:
	bool getIsMaxTime() const;
	static constexpr double MaxTimeTotalMilliseconds = 359999999; // new TimeCode(99, 59, 59, 999).TotalMilliseconds

	TimeCode(double totalMilliseconds);

	TimeCode();

	TimeCode(int hours, int minutes, int seconds, int milliseconds);

	double getTotalSeconds() const;
	void setTotalSeconds(double value);

	double getTotalMilliseconds() const;
	void setTotalMilliseconds(double value);

	TimeSpan getTimeSpan() const;
	void setTimeSpan(TimeSpan value);

	std::string ToString();

	std::string ToString(bool localize);

	std::string ToDisplayString();

	std::string ToHHMMSSFF();
	std::string ToASSString();

	std::string ToShortDisplayString();

	std::string ToShortStringHHMMSSFF();

	std::string ToShortString(bool localize = false);

private:
	std::string PrefixSign(const std::string &time);
};