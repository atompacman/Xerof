#pragma once
#include "TemperateForest.h"

class FruitTemperateForest : public TemperateForest
{
public:
	virtual ConsoleColor color(bool isNight) const
	{
		return isNight ? DARK_RED : RED;
	}
};