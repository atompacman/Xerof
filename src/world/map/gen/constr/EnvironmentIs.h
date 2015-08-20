#pragma once

#include <Constraint.h>
#include <Tile.h>

/*============================================================================\\
| Environment to replace is restricted to one type
|-----------------------------------------------------------------------------||
| Binary selection
\=============================================================================*/

class EnvironmentIs : public Constraint
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    EnvironmentIs(const Map& i_Map, Biome i_Type) :
        Constraint(i_Map),
        m_Type(i_Type)
    {}

    // WEIGHT
    double getWeightFor(Coord i_Coord) const
    {
        return m_Map(i_Coord).getEnvironment().getBiome() == m_Type;
    }

private:
    Biome m_Type;
};