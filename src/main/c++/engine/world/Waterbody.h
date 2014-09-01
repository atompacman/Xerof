#pragma once
#include "Background.h"

class Waterbody : public Background
{
public:
	virtual bool isPassable() const
	{
		return false;
	}
	virtual bool isDrinkable() const = 0;
	virtual bool isSolidLand() const
	{
		return false;
	}
};