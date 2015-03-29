#pragma once
#include <assert.h>
#include "Tile.h"

class Map
{
public:
    friend class MapGenerator;

	// CONSTRUCTOR/DESTRUCTOR
	Map(Dimensions i_Dim);
	~Map();

	// GETTERS
	const Tile&   getTile(Coord i_Coord) const;
    const Tile*** getTiles(Coord i_LowerLeft, Coord i_UpperRight) const;
    Coord         randCoord() const;

    // STATUS
    Dimensions  dim() const;
    UINT        area() const;

private:
    Dimensions m_Dim;
	Tile*      m_Tiles;
};