#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "ConstraintWithStrength.h"
#include "NeighbouringEnvConstraint.h"
/*============================================================================//
| The more a spot is surrounded by the same environment, the more probably the
| env. placement will be.
|-----------------------------------------------------------------------------||
| Parameters:
|   - The environment type to count
|   - The manhattan distance to the fartest 
|   - Strength : how critical is the effect of this constraint
\=============================================================================*/

class NeighbouringEnvAttraction : public NeighbouringEnvConstraint,
                                  public ConstraintWithStrength 
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    NeighbouringEnvAttraction(const Map& i_Map,
                              EnvType    i_EnvType,
                              unsigned int       i_Radius,
                              double     i_Strength) :
        Constraint(i_Map),
        NeighbouringEnvConstraint(i_Map, i_EnvType, i_Radius),
        ConstraintWithStrength(i_Map, i_Strength, false)
    {}

    // WEIGHT
    double getWeightFor(Coord i_Coord) const
    {
        return ConstraintWithStrength::getWeightFor(i_Coord);
    }

    double getSimpleWeightFor(Coord i_Coord) const
    {
        unsigned int neighbouringEnv(countNeighbourEnv(i_Coord));
        return (double) neighbouringEnv / (double)(m_Radius * m_Radius);
    }
};