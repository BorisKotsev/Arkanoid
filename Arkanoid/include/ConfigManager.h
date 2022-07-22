#pragma once

#include "defines.h"

#include <fstream>

class ConfigManager
{
public:
	ConfigManager();
	~ConfigManager();

	void load();
};
