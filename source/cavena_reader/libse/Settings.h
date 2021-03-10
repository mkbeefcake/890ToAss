#pragma once

#include <string>

class GeneralSettings
{
private:
	double DefaultFrameRate = 0;
	double CurrentFrameRate = 0;
	bool UseTimeFormatHHMMSSFF = false;
	std::string UppercaseLetters;

public:
	double getDefaultFrameRate() const;
	void setDefaultFrameRate(double value);

	double getCurrentFrameRate() const;
	void setCurrentFrameRate(double value);
	bool getUseTimeFormatHHMMSSFF() const;
	void setUseTimeFormatHHMMSSFF(bool value);
	std::string getUppercaseLetters() const;
	void setUppercaseLetters(const std::string &value);

	GeneralSettings();
};

class Settings
{
public:
	GeneralSettings *General = nullptr;
	static Settings *settings;

	virtual ~Settings()
	{
		delete General;
	}

	void Reset();

private:
	Settings();

public:
	static Settings *GetSettings();
};
