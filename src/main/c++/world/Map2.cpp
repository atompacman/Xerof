#include "Map2.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Map2::Map2() :
m_Tiles(new Tile*[area(MAP_DIMENSIONS)])
{}



Map2::~Map2()
{
	delete[] m_Tiles;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   GETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

const Tile* Map2::getTile(Coord i_Coord) const
{
    assert(i_Coord.x < MAP_DIMENSIONS.x);
    assert(i_Coord.y < MAP_DIMENSIONS.y);
    return m_Tiles[i_Coord.x + i_Coord.y * MAP_DIMENSIONS.x];
}