#pragma once

#include <Elem2D.h>

/*============================================================================\\
| The map
|-----------------------------------------------------------------------------||
| Is essentially an array of tiles that as accessors
\=============================================================================*/

class Tile;

class Map
{
public:
    friend class MapGenerator;

    // CONSTRUCTOR/DESTRUCTOR
    Map(Dimensions i_Dim);
    ~Map();

    // GETTERS
    const Tile& getTile(Coord i_Coord) const;
    Tile&       getTile(Coord i_Coord);
    Coord       randCoord() const;

    // STATUS
    Dimensions   dim() const;
    unsigned int area() const;

private:
    Dimensions m_Dim;
    Tile*      m_Tiles;

    // GETTERS
    unsigned int linearize(Coord i_Coord) const;
};