#pragma once
#include "Tile.h"
#include <assert.h>
#include <iomanip>
#include <random>
#include <stdlib.h>


///////////////////////////////////////////////////////////
//               MAP GENERATION PARAMETERS               //
///////////////////////////////////////////////////////////
// Land proportion (%)
const double LAND_PROPORTION = 0.4;

// Nb initial land tiles before growing the islands -------
// ex:
//   - < 15  = pangea
//   - 20-50 = small continents
//   - > 50  = archipelago
const UINT INITIAL_LAND_TILES = 120;

// Distance criteria weight -------------------------------
// ex:
//   - 0.1 = very dispersed 
//   - 0.5 = normal
//   - 1.5 = concentrated in the middle -------------------
const double DISTANCE_CRITERIA_WEIGHT = 0.2;

// Surrounding land criteria weight------------------------
// ex:
//   - 0.1 = very fractal landmass
//   - 1.0 = irregular landmass
//   - 2.0 = completely full landmass
const double SURROUNDING_LAND_CRITERIA_WEIGHT = 0.7;

// Tundra -------------------------------------------------
const double TUNDRA_PROPORTION = 0.3;
const UINT TUNDRA_RANDOMNESS_RADIUS = 8;

// Plain --------------------------------------------------
const double INITIAL_PLAIN_TILES = 30;
const double PLAIN_ALTITUDE_WEIGHT = 1.5;

// Rocky --------------------------------------------------
const double INITIAL_ROCKY_TILES = 100;
const double ROCKY_TILES_PROPORTION = 0.5;
const UINT ROCKY_ZONE_THICKNESS = 4;
///////////////////////////////////////////////////////////

const UINT LAND_TILES = (UINT)((double) area(MAP_DIMENSIONS) * LAND_PROPORTION);

class Map
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	Map();
	~Map();

	// SETTERS
	void setEnvironnement(Coord i_Coord, EnvType i_Type);

	// GETTERS
    Tile* getTile(Coord i_Coord) const;

private:
	Tile** m_Tiles;
	UINT m_PlacedInitPlains;
	UINT m_PlacedInitRockies;

    // CONSTRUCTOR/DESTRUCTOR
    void fillWithOcean();
	void generateLand();
	void placeInitialLandTiles();
	void growIslands();
	void setLandTile(Coord i_Coord);
	bool suitablePlainLocation(Coord i_Coord);
	bool suitableRockyLocation(Coord i_Coord);
	bool isLand(Coord i_Coord) const;

	// DISTANCE
	double computeDistanceWeight(Coord i_Coord) const;
	double computeAltitudeWeight(int y) const;
	double distFromEquatorProportion(int y) const;

	// SURROUNDING TILES
	double computeSurroundingLandWeight(Coord i_Coord) const;
	bool hasSurroundingLand(Coord i_Coord) const;
    bool hasSurroundingTileOfType(Coord i_Coord, EnvType i_Type) const;
	UINT countSurroundingLandTiles(Coord i_Coord) const;
    UINT countSurroundingTilesOfType(Coord i_Coord, EnvType i_Type) const;
};

static Coord randTile()
{
    return Coord(nextRand(1, MAP_DIMENSIONS.x - 2), 
                 nextRand(1, MAP_DIMENSIONS.y - 2));
}

static UINT linearize(Coord i_Coord)
{
    return i_Coord.x + i_Coord.y * MAP_DIMENSIONS.x;
}