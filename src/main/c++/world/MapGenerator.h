#pragma once
#include <assert.h>
#include <iomanip>
#include "constraint\Clustering.h"
#include "constraint\DistanceFromCenter.h"
#include "constraint\EnvironmentIs.h"
#include "Map2.h"
#include "MapConfig.h"
#include "..\utils\Random.h"

class MapGenerator
{
public:
	// GENERATION
	static Map2& generate(const MapConfig& i_Config);

private:
    static Map2*            s_Map;
    static const MapConfig* s_Config;

	// GENERATION
    static void fillWithOcean();
    static void placeInitialLandTiles();
    static void growLandmasses();
    static void generateEnv(EnvType      i_Type,
                            UINT         i_NumElem,
		                    Constraint** i_Constr, 
                            UINT         i_NumConstr, 
                            const char*  i_TaskDesc);
    static const Coord randCoord();
};

