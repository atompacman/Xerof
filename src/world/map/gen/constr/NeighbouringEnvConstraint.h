#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Constraint.h"
/*============================================================================//
| Abstract class that defines the main method of constraints concerning
| neighbouring environment: UINT countNeighbourEnv(Coord).
| The zone that is looked at is a square.
|-----------------------------------------------------------------------------||
| Parameters:
|   - The environment type to count
|   - The manhattan distance to the fartest tile
\=============================================================================*/

class NeighbouringEnvConstraint : public virtual Constraint
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    NeighbouringEnvConstraint(const Map& i_Map, 
                              EnvType    i_EnvType, 
                              UINT       i_Radius) :
        Constraint(i_Map),
        m_EnvType(i_EnvType),
        m_Radius(i_Radius)
    {}

    // WEIGHT
    UINT countNeighbourEnv(Coord i_Coord) const
    {
        UINT count(0);
        Coord coord(max(0, i_Coord.x - m_Radius), max(0, i_Coord.y - m_Radius));
        UINT endX(min(i_Coord.x + m_Radius + 1, m_Map.dim().x));
        UINT endY(min(i_Coord.y + m_Radius + 1, m_Map.dim().y));

        for (; coord.y < endY; ++coord.y) {
            for (; coord.x < endX; ++coord.x) {
                if (coord == i_Coord) {
                    continue;
                }
                if (m_Map.getTile(coord).getEnvironment().getType()==m_EnvType){
                    ++count;
                }
            }
        }
        return count;
    }

protected:
    EnvType m_EnvType;
    UINT    m_Radius;
};