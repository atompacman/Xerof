#pragma once
#include "MapElement.h"

class Background : public MapElement
{
public:
	virtual bool isSolidLand() const = 0;
};