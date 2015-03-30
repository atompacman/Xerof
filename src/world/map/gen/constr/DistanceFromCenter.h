#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <math.h>
//  | =   =   =   =   =   c=   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Constraint.h"
/*============================================================================//
| TODO
|-----------------------------------------------------------------------------||
| Todo
\=============================================================================*/

class DistanceFromCenter: public Constraint
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    DistanceFromCenter(const Map& i_Map, double i_Dispertion) :
        Constraint(i_Map),
        m_Dispertion(i_Dispertion) 
    {}

	// WEIGHT
    double getWeightFor(Coord i_Coord) const
	{
        DCoord mapRadius = toDCoord(m_Map.dim()) * 0.5;
        DCoord distToCenter = abs(toDCoord(i_Coord) - mapRadius) / mapRadius;
        return pow((1 - distToCenter.x) * (1 - distToCenter.y), m_Dispertion);
	}

private:
	double m_Dispertion;
};