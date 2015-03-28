#pragma once
#include "..\Map2.h"
#include "..\..\Parameters.h"

class Constraint
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Constraint(const Map2& i_Map) :
        m_Map(i_Map)
    {}

    // WEIGHT
    virtual float getWeightFor(Coord i_Coord) const = 0;

protected:
    Map2 m_Map;

    // COUNT SURROUNDING
    int countSurroundingEnvironOfType(Coord m_Coord, EnvType m_Type) const
    {
        int count = 0;
        for (int y = -1; y <= 1; ++y) {
            for (int x = -1; x <= 1; ++x) {
                if (x == 0 && y == 0) {
                    continue;
                }
                Tile tile = m_Map.getTile(Coord(m_Coord.x + x, m_Coord.y + y));
                if (tile.getEnvironment().getType() == m_Type) {
                    ++count;
                }
            }
        }
        return count;
    }
};