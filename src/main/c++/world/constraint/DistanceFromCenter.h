#pragma once
#include "Constraint.h"
#include "..\..\Parameters.h"
#include <math.h>

class DistanceFromCenter: public Constraint
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    DistanceFromCenter(float i_Dispoertion) : 
        m_Dispertion(i_Dispoertion) 
    {}

	// WEIGHT
	float getWeightFor(Coord i_Coord) const
	{
		float xMapRadius = MAP_DIMENSIONS.x / 2.0;
		float yMapRadius = MAP_DIMENSIONS.y / 2.0;
		float xWeight = 1 - abs((float)i_Coord.x - xMapRadius) / xMapRadius;
		float yWeight = 1 - abs((float)i_Coord.y - yMapRadius) / yMapRadius;
		return pow(xWeight * yWeight, m_Dispertion);
	}

private:
	float m_Dispertion;
};