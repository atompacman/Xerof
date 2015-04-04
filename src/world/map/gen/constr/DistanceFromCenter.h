#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "ConstraintWithStrength.h"
/*============================================================================//
| A tile has more chance to spawn close or far from center of the map
|-----------------------------------------------------------------------------||
| Parameters:
|   - Direction: attaction / repulsion
|   - Strength : how distance affect probabilities
\=============================================================================*/

class DistanceFromCenter : public ConstraintWithStrength
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    DistanceFromCenter(const Map& i_Map,
                       double     i_Strength,
                       bool       i_Attraction) :
        Constraint(i_Map),
        ConstraintWithStrength(i_Map, i_Strength, i_Attraction),
        m_MapCenter(toDCoord(m_Map.dim()) * 0.5)
    {}

	// WEIGHT
    double getSimpleWeightFor(Coord i_Coord) const
	{
        DCoord distToCenter = abs(toDCoord(i_Coord) - m_MapCenter)/m_MapCenter;
        return sqrt(distToCenter.x * distToCenter.x +
            distToCenter.y + distToCenter.y);
	}

private:
    DCoord m_MapCenter;
};