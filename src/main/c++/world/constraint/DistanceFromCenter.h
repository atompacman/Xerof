#pragma once
#include <math.h>
#include "Constraint.h"

class DistanceFromCenter: public Constraint
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    DistanceFromCenter(const Map2& i_Map, float i_Dispoertion) :
        Constraint(i_Map),
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