#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Constraint.h"
/*============================================================================//
| Abstract class that defines the main method of constraints concerning
| neighbouring environment: unsigned int countNeighbourEnv(Coord).
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
                              unsigned int       i_Radius) :
        Constraint(i_Map),
        m_EnvType(i_EnvType),
        m_Radius(i_Radius)
    {}

    // WEIGHT
    unsigned int countNeighbourEnv(Coord i_Coord) const
    {
        unsigned int count(0);
        unsigned int begX(i_Coord.x < m_Radius ? 0 : i_Coord.x - m_Radius);
        unsigned int begY(i_Coord.y < m_Radius ? 0 : i_Coord.y - m_Radius);
        unsigned int endX(min(i_Coord.x + m_Radius + 1, m_Map.dim().x));
        unsigned int endY(min(i_Coord.y + m_Radius + 1, m_Map.dim().y));
        Coord coord;

        for (coord.y = begY; coord.y < endY; ++coord.y) {
            for (coord.x = begX; coord.x < endX; ++coord.x) {
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
    unsigned int    m_Radius;
};