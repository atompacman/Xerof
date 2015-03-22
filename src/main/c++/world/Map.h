#pragma once
#include "Tile.h"
#include "..\engine\internal\Logger.h"
#include <assert.h>
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
const int INITIAL_LAND_TILES = 120;

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
const int TUNDRA_RANDOMNESS_RADIUS = 8;

// Plain --------------------------------------------------
const double INITIAL_PLAIN_TILES = 30;
const double PLAIN_ALTITUDE_WEIGHT = 1.5;

// Rocky --------------------------------------------------
const double INITIAL_ROCKY_TILES = 100;
const double ROCKY_TILES_PROPORTION = 0.5;
const int ROCKY_ZONE_THICKNESS = 4;
///////////////////////////////////////////////////////////

const int LAND_TILES = (int)((double) MAP_DIMENSIONS.area() * LAND_PROPORTION);

static Coord<int> randTile()
{
	int x = nextRand(1, MAP_DIMENSIONS.x - 2);
	int y = nextRand(1, MAP_DIMENSIONS.y - 2);
	return Coord<int>(x, y);
}

static unsigned int linearize(Coord<int> coord)
{
	int linearization = coord.x + coord.y * MAP_DIMENSIONS.x;
	assert(linearization >= 0);
	return linearization;
}

class Map
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	Map();
	~Map();

	// SETTERS
	void setEnvironnement(Coord<int>, EnvType);

	// GETTERS
	Tile* getTile(Coord<int>) const;

private:
	Tile** tiles;
	int placedInitialPlainTiles;
	int placedInitialRockyTiles;

	// MAP GENERATION
	void fillWithOcean();
	void generateLand();
	void placeInitialLandTiles();
	void growIslands();
	void setLandTile(Coord<int>);
	bool suitablePlainLocation(Coord<int>);
	bool suitableRockyLocation(Coord<int>);
	bool isLand(Coord<int>) const;

	// DISTANCE
	double computeDistanceWeight(Coord<int>) const;
	double computeAltitudeWeight(int y) const;
	double distFromEquatorProportion(int y) const;

	// SURROUNDING TILES
	double computeSurroundingLandWeight(Coord<int>) const;
	bool hasSurroundingLand(Coord<int>) const;
	bool hasSurroundingTileOfType(Coord<int>, EnvType) const;
	int countSurroundingLandTiles(Coord<int>) const;
	int countSurroundingTilesOfType(Coord<int>, EnvType) const;
};