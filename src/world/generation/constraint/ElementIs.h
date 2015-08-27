#pragma once

#include <Constraint.h>
#include <JSONUtils.h>
#include <Tile.h>

/*============================================================================\\
| Element to replace is restricted to one type
|-----------------------------------------------------------------------------||
| Binary selection
\=============================================================================*/

class ElementIs : public Constraint
{
public:
    // FACTORY METHOD
    static Constraint* makeElementIsConstraint(
        const rapidjson::Value& i_CnstrntElem, const Map& i_Map)
    {
        return new ElementIs(i_Map, parseBiome(i_CnstrntElem, "Biome"));
    }

    // EVALUATE
    double evaluate(Biome i_Biome, Coord i_Coord) const
    {
        return m_Map(i_Coord).getEnvironment().getBiome() == m_Biome;
    }

private:
    // CONSTRUCTOR/DESTRUCTOR
    ElementIs(const Map& i_Map, Biome i_Biome) :
        Constraint(i_Map),
        m_Biome(i_Biome)
    {}

    Biome m_Biome;
};
