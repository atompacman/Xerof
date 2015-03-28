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
	static void generate(Map2& o_Map, const MapConfig& i_Config);

private:
	// GENERATION
    static void fillWithOcean(Map2& io_Map);
    static void placeInitialLandTiles(Map2& io_Map);
    static void growLandmasses(Map2& io_Map);
    static void generateEnvironment(Map2&        io_Map,
                                    EnvType      i_Type,
                                    UINT         i_NumElem,
		                            Constraint** i_Constr, 
                                    UINT         i_NumConstr, 
                                    const char*  i_TaskDesc);
    static Coord randTile();
};

