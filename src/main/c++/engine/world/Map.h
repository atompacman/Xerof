#pragma once
#include "environnement\Forest\TemperateForest.h"
#include "environnement\Grassland.h"
#include "environnement\Lake.h"
#include "environnement\Plain.h"
#include "environnement\Ocean.h"
#include "environnement\Rocky.h"
#include "environnement\Tundra.h"
#include "Random.h"
#include "Tile.h"
#include <assert.h>
#include <iostream>
#include <random>
#include <stdlib.h>

///////////////////////////////////////////////////////////
//               MAP GENERATION PARAMETERS               //
///////////////////////////////////////////////////////////

// Map size (length = x, height = y) ----------------------
const unsigned int MAP_LENGTH = 236;
const unsigned int MAP_HEIGHT = 73;

// Land proportion (%)
const double LAND_PROPORTION = 0.60; //0.60

// Nb initial land tiles before growing the islands -------
// ex:
//   - < 15  = pangea
//   - 20-50 = small continents
//   - > 50  = archipelago
const int INITIAL_LAND_TILES = 60;

// Distance criteria weight -------------------------------
// ex:
//   - 0.1 = very dispersed 
//   - 0.5 = normal
//   - 1.5 = concentrated in the middle -------------------
const double DISTANCE_CRITERIA_WEIGHT = 0.5;

// Surrounding land criteria weight------------------------
// ex:
//   - 0.1 = very fractal landmass
//   - 1.0 = irregular landmass
//   - 2.0 = completely full landmass
const double SURROUNDING_LAND_CRITERIA_WEIGHT = 0.8;

// Tundra -------------------------------------------------
const double TUNDRA_PROPORTION = 0.3;
const int TUNDRA_RANDOMNESS_RADIUS = 2;

// Plain --------------------------------------------------
const double INITIAL_PLAIN_TILES = 30;
const double PLAIN_ALTITUDE_WEIGHT = 1.5;

// Rocky --------------------------------------------------
const double INITIAL_ROCKY_TILES = 100;
const double ROCKY_TILES_PROPORTION = 0.5;
const int ROCKY_ZONE_THICKNESS = 4;
///////////////////////////////////////////////////////////

const int LAND_TILES = int(MAP_HEIGHT * MAP_LENGTH * LAND_PROPORTION);

struct RandCoord
{
	unsigned int x = nextRand(1, MAP_LENGTH - 2);
	unsigned int y = nextRand(1, MAP_HEIGHT - 2);
};


class Map
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	Map();
	~Map(){};

	// SETTERS
	void setEnvironnement(unsigned int x, unsigned int y, Background*);
	void setContent(unsigned int x, unsigned int y, Foreground*);

	// GETTERS
	const Tile& getTile(unsigned int x, unsigned int y) const;

private:
	Tile tiles[MAP_LENGTH][MAP_HEIGHT];
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
	void detectLakeBorders();
	bool canReachLimitsFrom() const;

	// DISTANCE
	double computeDistanceWeight(const RandCoord&) const;
	double computeAltitudeWeight(unsigned int y) const;
	double distFromEquatorProportion(unsigned int y) const;

	// SURROUNDING TILES
	double computeSurroundingLandWeight(const RandCoord&) const;
	double hasSurroundingLand(const RandCoord&) const;
	double hasSurroundingPlain(const RandCoord&) const;
	int countSurroundingLandTiles(const RandCoord&) const;
	int countSurroundingPlainTiles(const RandCoord&) const;
	int countSurroundingRockyTiles(const RandCoord&) const;
};