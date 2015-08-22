#pragma once

#include <Border.h>
#include <Elem2D.h>
#include <Parameters.h>
#include <list>

/*============================================================================\\
| Generates map
|-----------------------------------------------------------------------------||
| Reads a configuration file that described a series of "phases" that consists
| of a series of constraints to be applied to tiles selected at random in order
| to model their probability of being place on the map.
\=============================================================================*/

enum   Biome;
struct Phase;
class  Map;
class  MapConfig;

namespace MapGenerator
{
    // GENERATION
    void generate(Map& o_Map, const char* i_MapConfigFile = DEFAULT_MAP_CONFIG);

    // GENERATION
    void placeBorders(const std::list<Border>& i_Borders);
    void fillWithInitialBiome(Biome i_InitBiome);
    void executeMapGenPhase(const Phase& i_Phase);
    void runOverpass();
    void removeLonelyTiles(const Biome& i_ChangedBiome, 
                           const Coord& i_ReadCoord);
    const Coord randCoord();
};