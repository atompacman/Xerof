#pragma once
#include <assert.h>
#include "Tile.h"

class Map2
{
public:
    friend class MapGenerator;

	// CONSTRUCTOR/DESTRUCTOR
	Map2();
	~Map2();

	// GETTERS
	const Tile& getTile(Coord i_Coord) const;

private:
	Tile** m_Tiles;
};