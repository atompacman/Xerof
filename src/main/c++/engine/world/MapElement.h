#pragma once
#include "..\console\ConsoleColor.h"

class MapElement
{
public:
	virtual ConsoleColor color(bool isNight) const = 0;
	virtual bool isPassable() const = 0;
};