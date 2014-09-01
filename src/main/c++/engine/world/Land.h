#pragma once
#include "Background.h"
#include "Temperature.h"

class Land : public Background
{
public:
	virtual bool isPassable() const
	{
		return true;
	}
	virtual Temperature getTemperature(bool isNight) const = 0;
	virtual bool isSolidLand() const
	{
		return true;
	}
};