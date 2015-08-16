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

#define M_SQRT2 1.41421356237309504880

class DistanceFromCenter : public ConstraintWithStrength
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    DistanceFromCenter(const Map& i_Map,
                       double     i_Strength,
                       bool       i_Attraction) :
                           Constraint(i_Map),
        ConstraintWithStrength(i_Map, i_Strength, i_Attraction),
        m_MapCenter(toDCoord(m_Map.dim()) * 0.5),
        m_ConvFactor(m_MapCenter * M_SQRT2)
    {}

    // WEIGHT
    double getSimpleWeightFor(Coord i_Coord) const
    {
        DCoord dist = abs(toDCoord(i_Coord) - m_MapCenter) / m_ConvFactor;
        return sqrt(dist.x * dist.x + dist.y * dist.y);
    }

private:
    DCoord m_MapCenter;
    DCoord m_ConvFactor;
};