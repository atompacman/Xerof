#pragma once
#include <assert.h>
#include "constraint\Clustering.h"
#include "constraint\DistanceFromCenter.h"
#include "constraint\EnvironmentIs.h"
#include "Map.h"
#include "MapConfig.h"
#include "..\utils\ProgressLogger.h"
#include "..\utils\Random.h"

typedef std::vector<const Constraint*> Constrs;

class MapGenerator
{
public:
	// GENERATION
	static Map& generate(const MapConfig& i_Config);

private:
    static Map*             s_Map;
    static const MapConfig* s_Config;

	// GENERATION
    static void placeInitialLandTiles();
    static void growLandmasses();
    static void generateEnv(EnvType        i_Type,
                            UINT           i_NumElem,
                            const Constrs& i_Constr, 
                            const char*    i_TaskDesc);
    static const Coord randCoord();
};

