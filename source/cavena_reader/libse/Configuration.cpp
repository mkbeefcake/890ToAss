#include "Configuration.h"


std::string Configuration::DefaultLinuxFontName = "DejaVu Serif";
Configuration* Configuration::Instance = new Configuration();

Configuration::Configuration()
{
	//_encodings = GetAvailableEncodings();
	_settings = Settings::GetSettings();
}

Settings *Configuration::getSettings()
{
	return Instance->_settings;
}
/*
std::vector<Encoding*> Configuration::GetAvailableEncodings()
{
	auto encodings = std::vector<Encoding*>();
	for (auto ei : Encoding::GetEncodings())
	{
		try
		{
			encodings.push_back(Encoding::GetEncoding(ei->CodePage));
		}
		catch (...)
		{
			// though advertised, this code page is not supported
		}
	}
	return encodings;// .AsEnumerable();
}*/
