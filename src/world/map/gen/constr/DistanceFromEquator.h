#pragma once

//===========================================================================\\
//  | =   =   =   =   =   c=   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "ConstraintWithStrength.h"
/*============================================================================//
| A tile has more chance to spawn close or far from the equator
|-----------------------------------------------------------------------------||
| Parameters:
|   - Direction: attaction / repulsion
|   - Strength : how distance affect probabilities
\=============================================================================*/

class DistanceFromEquator : public ConstraintWithStrength
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    DistanceFromEquator(const Map& i_Map, 
                        double     i_Strength, 
                        bool       i_Attraction) :
        Constraint(i_Map),
        ConstraintWithStrength(i_Map, i_Strength, i_Attraction),
        m_Equator((double) i_Map.dim().y * 0.5)
    {}

    // WEIGHT
    double getSimpleWeightFor(Coord i_Coord) const
    {
        return abs(((double)i_Coord.y - m_Equator) / m_Equator);
    }

private:
    double m_Equator;
};

