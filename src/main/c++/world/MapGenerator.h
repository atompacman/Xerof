#pragma once
#include "..\utils\Random.h"
#include "Map2.h"
#include "constraint\Clustering.h"
#include "constraint\DistanceFromCenter.h"
#include "constraint\EnvironmentIs.h"
#include "..\engine\internal\Logger.h"

static Coord<int> randTile()
{
	int x = nextRand(OCEAN_MARGINS, MAP_DIMENSIONS.x - 2 * OCEAN_MARGINS);
	int y = nextRand(OCEAN_MARGINS, MAP_DIMENSIONS.y - 2 * OCEAN_MARGINS);
	return Coord<int>(x, y);
}


class MapGenerator: public Map2
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	MapGenerator();

	// GENERATION
	Map2* generate();

private:
	// GENERATION
	void fillWithOcean();
	void placeInitialLandTiles();
	void growLandmasses();
	void generateEnvironment(EnvType type, unsigned int elemQuant,
		Constraint** constraints, int nbConst, const char* taskDesc);
	void printProgress(const char* taskDesc, unsigned int progress);
};