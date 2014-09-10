#pragma once
#include "..\Parameters.h"
#include "..\utils\Random.h"
#include "Tile.h"
#include <assert.h>
#include <random>
#include <stdlib.h>


///////////////////////////////////////////////////////////
//               MAP GENERATION PARAMETERS               //
///////////////////////////////////////////////////////////

const int MAP_WIDTH_IN_TILES = 128; //128
const int MAP_HEIGHT_IN_TILES = 96;  // 96
const int TOTAL_NB_TILES = MAP_WIDTH_IN_TILES * MAP_HEIGHT_IN_TILES;

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

const int LAND_TILES = (int)((double)TOTAL_NB_TILES * LAND_PROPORTION);

struct RandCoord
{
	unsigned int x = nextRand(1, MAP_WIDTH_IN_TILES - 2);
	unsigned int y = nextRand(1, MAP_HEIGHT_IN_TILES - 2);
};


class Map
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	Map();
	~Map();

	// SETTERS
	void setEnvironnement(unsigned int x, unsigned int y, EnvType);

	// GETTERS
	Tile* getTile(unsigned int x, unsigned int y) const;

private:
	Tile** tiles;
	int placedInitialPlainTiles;
	int placedInitialRockyTiles;

	// MAP GENERATION
	void fillWithOcean();
	void generateLand();
	void placeInitialLandTiles();
	void growIslands();
	void setLandTile(const RandCoord&);
	bool suitablePlainLocation(const RandCoord&);
	bool suitableRockyLocation(const RandCoord&);
	bool isLand(unsigned int x, unsigned int y) const;

	// DISTANCE
	double computeDistanceWeight(const RandCoord&) const;
	double computeAltitudeWeight(unsigned int y) const;
	double distFromEquatorProportion(unsigned int y) const;

	// SURROUNDING TILES
	double computeSurroundingLandWeight(const RandCoord&) const;
	bool hasSurroundingLand(const RandCoord&) const;
	bool hasSurroundingTileOfType(const RandCoord&, EnvType) const;
	int countSurroundingLandTiles(const RandCoord&) const;
	int countSurroundingTilesOfType(const RandCoord&, EnvType) const;
};