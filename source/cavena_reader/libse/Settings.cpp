#include "Settings.h"

double GeneralSettings::getDefaultFrameRate() const
{
	return DefaultFrameRate;
}

void GeneralSettings::setDefaultFrameRate(double value)
{
	DefaultFrameRate = value;
}

double GeneralSettings::getCurrentFrameRate() const
{
	return CurrentFrameRate;
}

void GeneralSettings::setCurrentFrameRate(double value)
{
	CurrentFrameRate = value;
}

bool GeneralSettings::getUseTimeFormatHHMMSSFF() const
{
	return UseTimeFormatHHMMSSFF;
}

void GeneralSettings::setUseTimeFormatHHMMSSFF(bool value)
{
	UseTimeFormatHHMMSSFF = value;
}

std::string GeneralSettings::getUppercaseLetters() const
{
	return UppercaseLetters;
}

void GeneralSettings::setUppercaseLetters(const std::string &value)
{
	UppercaseLetters = value;
}

GeneralSettings::GeneralSettings()
{
	setUppercaseLetters("ABCDEFGHIJKLMNOPQRSTUVWZYXÆØÃÅÄÖÉÈÁÂÀÇÊÍÓÔÕÚŁАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯĞİŞÜÙÁÌÑÎ");
	setDefaultFrameRate(25);
	setCurrentFrameRate(getDefaultFrameRate());
	setUseTimeFormatHHMMSSFF(false);
}

Settings *Settings::settings = nullptr;
void Settings::Reset()
{
	General = new GeneralSettings();
}

Settings::Settings()
{
	Reset();
}

Settings *Settings::GetSettings()
{
	if (settings == nullptr)
	{
		settings = new Settings();
	}
	return settings;
}
