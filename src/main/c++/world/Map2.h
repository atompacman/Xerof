#pragma once
#include <assert.h>
#include "Tile.h"

class Map2
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	Map2();
	~Map2();

	// GETTERS
	const Tile* getTile(Coord i_Coord) const;

protected:
	Tile** m_Tiles;
};

static UINT linearize(Coord i_Coord)
{
    return i_Coord.x + i_Coord.y * MAP_DIMENSIONS.x;
}