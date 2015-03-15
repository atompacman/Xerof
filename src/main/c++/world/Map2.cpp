#include "Map2.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Map2::Map2()
{
	tiles = new Tile*[MAP_DIMENSIONS.area()];
}

Map2::~Map2()
{
	Coord<int> coord;
	for (coord.y = 0; coord.y < MAP_DIMENSIONS.y; ++coord.y) {
		for (coord.x = 0; coord.x < MAP_DIMENSIONS.x; ++coord.x) {
			delete tiles[linearize(coord)];
		}
	}
	delete[] tiles;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   GETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

const Tile* Map2::getTile(Coord<int> coord) const
{
	assert(coord.x < MAP_DIMENSIONS.x);
	assert(coord.y < MAP_DIMENSIONS.y);
	return tiles[linearize(coord)];
}