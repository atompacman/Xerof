#pragma once
#include <assert.h>
#include "Tile.h"

class Map2
{
public:
    friend class MapGenerator;

	// CONSTRUCTOR/DESTRUCTOR
	Map2(Dimensions i_Dim);
	~Map2();

	// GETTERS
	const Tile& getTile(Coord i_Coord) const;
    Dimensions  dim() const;
    UINT        area() const;

private:
    Dimensions m_Dim;
	Tile**     m_Tiles;
};