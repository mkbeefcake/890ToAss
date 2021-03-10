#pragma once
class TimeSpan
{
public :
	long	Ticks;
	double TotalMilliseconds;
	double TotalSecs;
	double TotalMinutes;
	double TotalHours;
	double TotalDays;

	int Milliseconds;
	int Seconds;
	int Minutes;
	int Hours;
	int Days;

	TimeSpan();
	TimeSpan(double totalMilliSecs);
	TimeSpan(int hours, int minutes, int seconds);

	TimeSpan Add(TimeSpan& add_span);

	static TimeSpan FromMilliseconds(double totalMilliSecs);

};

