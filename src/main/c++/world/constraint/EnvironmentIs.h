#pragma once
#include "..\Map2.h"
#include "Constraint.h"

class EnvironmentIs: public Constraint
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	EnvironmentIs(EnvType type): type(type) {}

	// WEIGHT
	float getWeightFor(Coord<int> coord) const
	{
		return map->getTile(coord)->getEnvironment()->getType() == type;
	}

private:
	EnvType type;
};