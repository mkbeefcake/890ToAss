#pragma once

#include "Settings.h"
#include "../../common/define.h"
class Configuration
{
private:
	static Configuration *Instance;

	Settings *_settings;
	//std::vector<Encoding*> _encodings;
public:
	static std::string DefaultLinuxFontName;

	virtual ~Configuration()
	{
		delete _settings;
	}

private:
	Configuration();

public:
	static Settings *getSettings();

private:
	//static std::vector<Encoding*> GetAvailableEncodings();

};
