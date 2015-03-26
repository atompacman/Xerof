#pragma once
#include "..\Map2.h"
#include "..\..\Parameters.h"

class Constraint
{
public:
	// WEIGHT
	virtual float getWeightFor(Coord i_Coord) const = 0;

	// SETTERS
	static void setMap(Map2* i_Map) { s_Map = i_Map; }

protected:
	static Map2* s_Map;

	// COUNT SURROUNDING
	int countSurroundingEnvironOfType(Coord m_Coord, EnvType m_Type) const
	{
		int count = 0;
		for (int y = -1; y <= 1; ++y) {
			for (int x = -1; x <= 1; ++x) {
				Coord currCoord = Coord(m_Coord.x + x, m_Coord.y + y);
				const Tile* tile = s_Map->getTile(currCoord);
				if (tile->getEnvironment().getType() == m_Type) {
					++count;
				}
			}
		}
		return count;
	}
};