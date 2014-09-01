#pragma once
#include "Land.h"
#include "Random.h"

class Grassland : public Land
{
public:
	virtual ConsoleColor color(bool isNight) const
	{
		return isNight ? DARK_GREEN : GREEN;
	}
	virtual Temperature getTemperature(bool isNight) const
	{
		Temperature average = isNight ? Temperature(18.0) : Temperature(22.0);
		return average + nextRand(-5, 5);
	}
};