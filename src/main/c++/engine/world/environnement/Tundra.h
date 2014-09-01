#pragma once
#include "Land.h"

class Tundra : public Land
{
public:
	virtual ConsoleColor color(bool isNight) const
	{
		return isNight ? LIGHT_GRAY : WHITE;
	}
	virtual Temperature getTemperature(bool isNight) const
	{
		Temperature average = isNight ? Temperature(-25.0) : Temperature(-10.0);
		return average + nextRand(-2, 2);
	}
};