#pragma once
#include "environnement\Grassland.h"
#include "environnement\Forest\TemperateForest.h"
#include "environnement\Ocean.h"
#include "Tile.h"
#include "Random.h"
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
const double LAND_PROPORTION = 0.60;

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
const double SURROUNDING_LAND_CRITERIA_WEIGHT = 1.0;
///////////////////////////////////////////////////////////


struct RandCoord
{
	unsigned int x = nextRand(1, MAP_LENGTH - 2);
	unsigned int y = nextRand(1, MAP_HEIGHT - 2);
};

const double LAND_TILES = int(MAP_HEIGHT * MAP_LENGTH * LAND_PROPORTION);


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

	// MAP GENERATION
	void fillWithOcean();
	void generateLand();
	void placeInitialLandTiles();
	void growIslands();
	bool suitableForAForest(unsigned int x, unsigned int y) const;
	double computeDistanceWeight(const RandCoord&) const;
	double computeSurroundingLandWeight(const RandCoord&) const;
	bool isLand(unsigned int x, unsigned int y) const;
};