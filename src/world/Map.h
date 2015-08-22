#pragma once

#include <Array2D.h>
#include <Elem2D.h>
#include <Random.h>
#include <Tile.h>

/*============================================================================\\
| The map
|-----------------------------------------------------------------------------||
| Is essentially an array of tiles that as accessors
\=============================================================================*/

class Map : public Array2D<Tile>
{
public:
    // GETTERS
    Coord getRandomCoord() const 
    { 
        return Coord(randUINT(m_Dim.x - 1), randUINT(m_Dim.y - 1)); 
    }
};
