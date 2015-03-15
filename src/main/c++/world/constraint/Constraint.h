#pragma once
#include "..\Map2.h"

class Constraint
{
public:
	// WEIGHT
	virtual float getWeightFor(Coord<int> coord) const = 0;

	// SETTERS
	static void setMap(Map2* theMap) { map = theMap; }

protected:
	static Map2* map;

	// COUNT SURROUNDING
	int countSurroundingEnvironOfType(Coord<int> coord, EnvType type) const
	{
		int count = 0;
		for (int y = -1; y <= 1; ++y) {
			for (int x = -1; x <= 1; ++x) {
				Coord<int> currCoord = Coord<int>(coord.x + x, coord.y + y);
				const Tile* tile = map->getTile(currCoord);
				if (tile->getEnvironment()->getType() == type) {
					++count;
				}
			}
		}
		return count;
	}
};