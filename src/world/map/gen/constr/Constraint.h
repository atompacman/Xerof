#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <stdlib.h>
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include "rapidjson\document.h"
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\src\utils\Elem2D.h"
#include "..\..\Map.h"
/*============================================================================//
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