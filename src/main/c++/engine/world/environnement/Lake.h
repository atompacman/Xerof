#pragma once
#include "Waterbody.h"

class Lake : public Waterbody
{
public:
	virtual ConsoleColor color(bool isNight) const
	{
		return isNight ? DARK_CYAN : CYAN;
	}
	virtual bool isDrinkable() const
	{
		return true;
	}
};