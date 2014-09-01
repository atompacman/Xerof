#pragma once
#include "Waterbody.h"

class Ocean : public Waterbody
{
public:
	virtual ConsoleColor color(bool isNight) const
	{
		return isNight ? DARK_BLUE : BLUE;
	}
	virtual bool isDrinkable() const
	{
		return false;
	}
};