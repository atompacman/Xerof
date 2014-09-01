#pragma once
#include "Foreground.h"

class Forest : public Foreground
{
public:
	virtual ConsoleColor color(bool isNight) const
	{
		return isNight ? BLACK : DARK_GREEN;
	}
	virtual char character() const = 0;
};