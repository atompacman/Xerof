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
    return m_Tiles[linearize(i_Coord)];
}

Tile& Map::getTile(Coord i_Coord)
{
    assert(i_Coord < m_Dim);
    return m_Tiles[linearize(i_Coord)];
}

Coord Map::randCoord() const
{
    return Coord(randUINT(m_Dim.x - 1), randUINT(m_Dim.y - 1));
}

unsigned int Map::linearize(Coord i_Coord) const
{
    return i_Coord.x + i_Coord.y * m_Dim.x;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    STATUS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Dimensions Map::dim() const
{
    return m_Dim;
}

unsigned int Map::area() const
{
    return m_Dim.x * m_Dim.y;
}