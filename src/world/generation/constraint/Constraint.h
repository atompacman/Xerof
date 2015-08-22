#pragma once

#include <Elem2D.h>
#include <Map.h>
#include <rapidjson\document.h>
#include <stdlib.h>

/*============================================================================\\
| Constraint abstract class
|-----------------------------------------------------------------------------||
| Constraints computes the probabilty [0, 1] of an environment to be placed at a
| certain place of the map.
\=============================================================================*/

class Constraint
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Constraint(const Map& i_Map) :
        m_Map(i_Map)
    {}

    // WEIGHT
    virtual double getWeightFor(Coord i_Coord) const = 0;

protected:
    const Map& m_Map;
};