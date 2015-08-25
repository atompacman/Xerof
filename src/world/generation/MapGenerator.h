#pragma once

#include <Parameters.h>
#include <rapidjson\document.h>

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

// JSON configuration file elements
#define CONFIG_ROOT_ELEM            "XerofMapGeneratorConfig"
    #define DIM_ELEM                "Dimensions"
        #define DIM_WIDTH_SUB_ELEM  "Width"
        #define DIM_HEIGHT_SUB_ELEM "Height"

    #define INIT_BIOME_ELEM         "InitialBiome"

    #define BORDERS_ELEM            "Borders"
        #define WIDTH_ELEM          "Width"
        #define BIOME_ELEM          "Biome"
    
    #define PHASES_ELEM             "Phases"

// JSON configurations limits file elements
#define LIMITS_ROOT_ELEM            "XerofMapConfigLimits"
    #define MIN_MAP_SIZE_ELEM       "MinimumMapSize"
    #define MAX_MAP_SIZE_ELEM       "MaximumMapSize"

namespace MapGenerator
{
    // GENERATION
    void generate(Map& o_Map, const char* i_MapConfigFile = DEFAULT_MAP_CONFIG);

    // GENERATION (private functions)
    void initializeMapTiles();
    unsigned int parseMapDimension(const rapidjson::Value& i_Elem,
                                   const char*             i_SubElemName);
    void placeBorders();
    void generateBorder(Biome              i_Biome,
                        BasicDir           i_Side,
                        const std::string& i_SideName, 
                        unsigned int       i_Width);
    void fillWithInitialBiome();
    void fillBiomeRegion(Biome i_Biome, Coord i_ULCorner, Coord i_LRCorner);
    void executeEnvironmentPhases();
    void runOverpass();
    void removeLonelyTiles(const Biome& i_ChangedBiome, 
                           const Coord& i_ReadCoord);
    const Coord randCoord();
};