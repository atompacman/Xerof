#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <math.h>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Constraint.h"
/*============================================================================//
| Any constraint that has a parameter that shapes the probabilty of a tile to
| be placed depending of the value returned by the constraint.
|
| As the strength gets closer to infinity, the more sever this constraint is.
| The doNegate parameter indicate if the value returned by the child class
| should be negated before computed.
|-----------------------------------------------------------------------------||
| Parameters:
|   - Strength : how critical is the effect of this constraint
|   - Do Negate: Means that the more the "simple" weight is big, the less
|                probable the tile will be placed
\=============================================================================*/

class ConstraintWithStrength : public virtual Constraint
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    ConstraintWithStrength(const Map& i_Map,
                           double     i_Strength,
                           bool       i_DoNegate) :
        Constraint(i_Map),
        m_Strength(i_Strength),
        m_DoNegate(i_DoNegate)
    {}

    // WEIGHT
    double getWeightFor(Coord i_Coord) const
    {
        if (m_DoNegate) {
            return pow(1 - getSimpleWeightFor(i_Coord), m_Strength);
        }
        else {
            return pow(getSimpleWeightFor(i_Coord), m_Strength);
        }
    }

    virtual double getSimpleWeightFor(Coord i_Coord) const = 0;

private:
    double m_Strength;
    bool   m_DoNegate;
};