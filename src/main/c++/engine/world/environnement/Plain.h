#pragma once
#include "Land.h"

class Plain : public Land
{
public:
	virtual ConsoleColor color(bool isNight) const
	{
		return isNight ? DARK_YELLOW : YELLOW;
	}
	virtual Temperature getTemperature(bool isNight) const
	{
		Temperature average = isNight ? Temperature(22.0) : Temperature(28.0);
		return average + nextRand(-7, 7);
	}
};