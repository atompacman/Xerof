#pragma once

#include <Elem2D.h>
#include <rapidjson\document.h>
#include <Map.h>

/*============================================================================\\
| Constraint abstract class
|-----------------------------------------------------------------------------||
| Computes the probabilty [0, 1] of an environment to be placed at a certain
| place on the map.
\=============================================================================*/

class Constraint
{
public:
    // FACTORY
    static std::map<std::string, Constraint*(*)(
        const rapidjson::Value& i_CnstrntElem,
        const Map&              i_Map)> s_Factory;

    // EVALUATE
    virtual double evaluate(Biome i_Biome, Coord i_Coord) const = 0;

protected:
    // CONSTRUCTOR/DESTRUCTOR
    Constraint(const Map& i_Map) :
        m_Map(i_Map)
    {}

    const Map& m_Map;
};
