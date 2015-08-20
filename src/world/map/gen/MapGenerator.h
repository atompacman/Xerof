#pragma once

#include <Elem2D.h>

/*============================================================================\\
| Generates map
|-----------------------------------------------------------------------------||
| Reads a configuration file that described a series of "phases" that consists
| of a series of constraints to be applied to tiles selected at random in order
| to model their probability of being place on the map.
\=============================================================================*/

class  Map;
class  MapConfig;
enum   Biome;
struct Phase;

namespace MapGenerator
{
    // GENERATION
    void generate(Map& o_Map);
    void generate(Map& o_Map, const char* i_MapConfigFile);

    // GENERATION
    void placeBorders();
    void fillWithInitEnv();
    void executeMapGenPhase(const Phase& i_Phase);
    void runOverpass();
    void removeLonelyTiles(const Biome& i_ChangedBiome, 
                           const Coord& i_ReadCoord);
    const Coord randCoord();
};