#pragma once
#include "MapElement.h"

class Foreground : public MapElement
{
public:
	virtual char character() const = 0;
	virtual bool isPassable() const
	{
		return false;
	}
};