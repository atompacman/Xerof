#pragma once
#include "..\..\Parameters.h"
#include "Constraint.h"
#include <math.h>

class DistanceFromCenter: public Constraint
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	DistanceFromCenter(float dispertion) : dispertion(dispertion) {}

	// WEIGHT
	float getWeightFor(Coord<int> coord) const
	{
		float xMapRadius = MAP_DIMENSIONS.x / 2.0;
		float yMapRadius = MAP_DIMENSIONS.y / 2.0;
		float xWeight = 1 - abs((float)coord.x - xMapRadius) / xMapRadius;
		float yWeight = 1 - abs((float)coord.y - yMapRadius) / yMapRadius;
		return pow(xWeight * yWeight, dispertion);
	}

private:
	float dispertion;
};