#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <assert.h>
#include <vector>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
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
| Reads a configuration file that described a series of "phases" that consists
| of a series of constraints to be applied to tiles selected at random in order
| to model their probability of being place on the map.
\=============================================================================*/

class MapGenerator
{
public:
	// GENERATION
    static Map& generate();
    static Map& generate(const char* i_MapConfigFile);

private:
    // Temporary
    static Map*       s_Map;
    static MapConfig* s_Config;
    static Coord      s_ULCorner;
    static Coord      s_LRCorner;

	// GENERATION
    static void placeBorders();
    static void fillWithInitEnv();
    static void executeMapGenPhase(const Phase& i_Phase);

    static const Coord randCoord();
};

