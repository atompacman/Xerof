#pragma once

#include <Constraint.h>
#include <Tile.h>

/*============================================================================\\
| Abstract class that defines the main method of constraints concerning
| neighbouring environment: UINT countNeighbourEnv(Coord).
| The zone that is looked at is a square.
|-----------------------------------------------------------------------------||
| Parameters:
|   - The environment type to count
|   - The manhattan distance to the fartest tile
\=============================================================================*/

class NearbyElemConstraint : public virtual Constraint
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    NearbyElemConstraint(const Map& i_Map, unsigned int i_Radius) :
        Constraint(i_Map),
        m_Radius(i_Radius)
    {}

    // EVALUATE
    unsigned int countNearbyBiome(Biome i_Biome, Coord i_Coord) const
    {
        unsigned int count(0);
        unsigned int begX(i_Coord.x < m_Radius ? 0 : i_Coord.x - m_Radius);
        unsigned int begY(i_Coord.y < m_Radius ? 0 : i_Coord.y - m_Radius);
        unsigned int endX(min(i_Coord.x + m_Radius + 1, m_Map.width()));
        unsigned int endY(min(i_Coord.y + m_Radius + 1, m_Map.height()));
        Coord coord;

        for (coord.y = begY; coord.y < endY; ++coord.y) {
            for (coord.x = begX; coord.x < endX; ++coord.x) {
                if (coord == i_Coord) {
                    continue;
                }
                if (m_Map(coord).getEnvironment().getBiome() == i_Biome){
                    ++count;
                }
            }
        }
        return count;
    }

protected:
    unsigned int m_Radius;
};
