#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <assert.h>
#include <vector>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "constr\Clustering.h"
#include "constr\Constraint.h"
#include "constr\DistanceFromCenter.h"
#include "constr\EnvironmentIs.h"
#include "..\Map.h"
#include "config\MapConfig.h"
#include "..\src\utils\ProgressLogger.h"
#include "..\src\utils\Random.h"
/*============================================================================||
| Generates map
|-----------------------------------------------------------------------------||
| In constructions
\=============================================================================*/

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

