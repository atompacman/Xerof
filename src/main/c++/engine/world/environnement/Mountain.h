#pragma once
#include "Land.h"

class Mountain : public Land
{
public:
	virtual ConsoleColor color(bool isNight) const
	{
		return isNight ? GRAY : LIGHT_GRAY;
	}
	virtual Temperature getTemperature(bool isNight) const
	{
		Temperature average = isNight ? Temperature(5.0) : Temperature(15.0);
		return average + nextRand(-10, 10);
	}
};