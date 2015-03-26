#pragma once
#include "constraint\Clustering.h"
#include "constraint\DistanceFromCenter.h"
#include "constraint\EnvironmentIs.h"
#include "Map2.h"
#include "..\utils\Random.h"
#include <iomanip>

class MapGenerator: public Map2
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	MapGenerator();

	// GENERATION
	Map2* generate();

private:
	// GENERATION
	void fillWithOcean();
	void placeInitialLandTiles();
	void growLandmasses();
	void generateEnvironment(EnvType      i_Type, 
                             UINT         i_NumElem,
		                     Constraint** i_Constr, 
                             int          i_NumConstr, 
                             const char*  i_TaskDesc);
    void printProgress(const char* i_TaskDesc, UINT i_Progress);
};

static Coord randTile()
{
    int x = nextRand(OCEAN_MARGINS, MAP_DIMENSIONS.x - 2 * OCEAN_MARGINS);
    int y = nextRand(OCEAN_MARGINS, MAP_DIMENSIONS.y - 2 * OCEAN_MARGINS);
    return Coord(x, y);
}