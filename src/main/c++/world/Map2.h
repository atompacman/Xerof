#pragma once
#include "Tile.h"
#include <assert.h>

static unsigned int linearize(Coord<int> coord)
{
	int linearization = coord.x + coord.y * MAP_DIMENSIONS.x;
	assert(linearization >= 0);
	return linearization;
}


class Map2
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	Map2();
	~Map2();

	// GETTERS
	const Tile* getTile(Coord<int>) const;

protected:
	Tile** tiles;
};