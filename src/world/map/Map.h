#pragma once

#include <Array2D.h>
#include <Elem2D.h>
#include <Tile.h>

/*============================================================================\\
| The map
|-----------------------------------------------------------------------------||
| Is essentially an array of tiles that as accessors
\=============================================================================*/

class Map : public Array2D<Tile>
{
public:
    friend class MapGenerator;

    // CONSTRUCTOR/DESTRUCTOR
    Map(Dimensions i_Dim);

    // GETTERS
    Coord getRandomCoord() const;
};