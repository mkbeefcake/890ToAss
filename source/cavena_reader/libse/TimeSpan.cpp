#include "TimeSpan.h"

TimeSpan::TimeSpan()
{
	TotalMilliseconds = 0;
	TotalSecs = 0;
	TotalMinutes = 0;
	TotalHours = 0;
	TotalDays = 0;

	Milliseconds = 0;
	Seconds = 0;
	Minutes = 0;
	Hours = 0;
	Days = 0;
}

TimeSpan::TimeSpan(int hours, int minutes, int seconds)
{
	TimeSpan((double)(((hours * 60 + minutes) * 60 + seconds) * 1000));
}

TimeSpan::TimeSpan(double totalMilliSecs)
{
	Ticks = totalMilliSecs * 10;
	totalMilliSecs += 0.5;
	TotalMilliseconds = totalMilliSecs;
	TotalSecs = TotalMilliseconds / 1000;
	TotalMinutes = TotalSecs / 60;
	TotalHours = TotalMinutes / 60;
	TotalDays = TotalHours / 24;
	Days = (int)TotalDays;
	Hours = (int)(TotalHours - Days * 24);
	Minutes = (int)(TotalMinutes - (Days * 24 + Hours) * 60);
	Seconds = (int)(TotalSecs - ((Days * 24 + Hours) * 60 + Minutes) * 60);
	Milliseconds = (int)(TotalMilliseconds - (((Days * 24 + Hours) * 60 + Minutes) * 60 + Seconds) * 1000);
}

TimeSpan TimeSpan::Add(TimeSpan& add_span)
{
	TimeSpan new_span(this->TotalMilliseconds + add_span.TotalMilliseconds);
	return new_span;
}

TimeSpan TimeSpan::FromMilliseconds(double totalMilliSecs)
{
	TimeSpan time_span(totalMilliSecs);
	return time_span;
}