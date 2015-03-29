#include "Map.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Map::Map(Dimensions i_Dim) :
m_Dim(i_Dim),
m_Tiles(new Tile[m_Dim.x * m_Dim.y])
{}

Map::~Map()
{
	delete[] m_Tiles;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Tile& Map::getTile(Coord i_Coord) const
{
    assert(i_Coord < m_Dim);
    return m_Tiles[i_Coord.x + i_Coord.y * m_Dim.x];
}

const Tile*** Map::getTiles(Coord i_LowerLeft, Coord i_UpperRight) const
{
    assert(i_LowerLeft < i_UpperRight);

    const Tile*** tiles = new const Tile**[i_UpperRight.y - i_LowerLeft.y];

    for (UINT y = 0; y < i_UpperRight.y - i_LowerLeft.y; ++y) {
        tiles[y] = new const Tile*[i_UpperRight.x - i_LowerLeft.x];
        for (UINT x = 0; x < i_UpperRight.x - i_LowerLeft.x; ++x) {
            tiles[y][x] = &m_Tiles[y * m_Dim.x + x];
        }
    }
    return tiles;
}

Coord Map::randCoord() const
{
    return Coord(randUINT(m_Dim.x - 1), randUINT(m_Dim.y - 1));
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    STATUS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Dimensions Map::dim() const
{
    return m_Dim;
}

UINT Map::area() const
{
    return m_Dim.x * m_Dim.y;
}