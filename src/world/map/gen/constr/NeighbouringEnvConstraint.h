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
                              Biome    i_EnvType, 
                              UINT       i_Radius) :
        Constraint(i_Map),
        m_EnvType(i_EnvType),
        m_Radius(i_Radius)
    {}

    // WEIGHT
    UINT countNeighbourEnv(Coord i_Coord) const
    {
        UINT count(0);
        UINT begX(i_Coord.x < m_Radius ? 0 : i_Coord.x - m_Radius);
        UINT begY(i_Coord.y < m_Radius ? 0 : i_Coord.y - m_Radius);
        UINT endX(min(i_Coord.x + m_Radius + 1, m_Map.dim().x));
        UINT endY(min(i_Coord.y + m_Radius + 1, m_Map.dim().y));
        Coord coord;

        for (coord.y = begY; coord.y < endY; ++coord.y) {
            for (coord.x = begX; coord.x < endX; ++coord.x) {
                if (coord == i_Coord) {
                    continue;
                }
                if (m_Map.getTile(coord).getEnvironment().getBiome()==m_EnvType){
                    ++count;
                }
            }
        }
        return count;
    }

protected:
    Biome m_EnvType;
    UINT    m_Radius;
};