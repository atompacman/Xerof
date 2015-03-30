#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <stdlib.h>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\src\utils\Elem2D.h"
#include "..\..\Map.h"
/*============================================================================//
| Constraint abstract class
|-----------------------------------------------------------------------------||
| Todo
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

    // COUNT SURROUNDING
    UINT countSurroundingEnvironOfType(Coord m_Coord,EnvType m_Type) const
    {
        UINT count(0);
        Coord coord;
        for (coord.y = max(0, m_Coord.y - 1);
             coord.y < min(m_Coord.y + 2, m_Map.dim().y); ++coord.y) {
            for (coord.x = max(0, m_Coord.x - 1);
                 coord.x < min(m_Coord.x + 2, m_Map.dim().x); ++coord.x) {
                if (coord == m_Coord) {
                    continue;
                }
                if (m_Map.getTile(coord).getEnvironment().getType() == m_Type) {
                    ++count;
                }
            }
        }
        return count;
    }
};