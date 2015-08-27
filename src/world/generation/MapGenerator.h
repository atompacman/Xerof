#pragma once

#include <list>
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
class  Constraint;
struct Phase;
class  Map;

// JSON configuration file elements
static const std::string CONFIG_ROOT_ELEM    ("XerofMapGeneratorConfig");
static const std::string DIM_ELEM               ("Dimensions");
static const std::string DIM_WIDTH_SUB_ELEM         ("Width");
static const std::string DIM_HEIGHT_SUB_ELEM        ("Height");
static const std::string BORDERS_ELEM           ("Borders");
static const std::string WIDTH_ELEM                 ("Width");
static const std::string BIOME_ELEM                 ("Biome");
static const std::string INIT_BIOME_ELEM        ("InitialBiome");
static const std::string PHASES_ELEM            ("Phases");
static const std::string QTY_ELEM                   ("Quantity");
static const std::string RELATIVE_ELEM                  ("Relative");
static const std::string ABSOLUTE_ELEM                  ("Absolute");
static const std::string BIOMES_PROP_ELEM       ("BiomesProportions");
static const std::string CONSTRAINTS_ELEM       ("Constraints");
static const std::string STRENGTH_ELEM              ("Strength");
static const std::string MIN_ELEM                   ("Min");
static const std::string MAX_ELEM                   ("Max");
static const std::string RADIUS_ELEM                ("Radius");
static const std::string MAX_TRIES_ELEM         ("MaxNumTriesBeforeSkipping");

// JSON configurations limits file elements
static const std::string LIMITS_ROOT_ELEM   ("XerofMapConfigLimits");
static const std::string MIN_MAP_SIZE_ELEM      ("MinimumMapSize");
static const std::string MAX_MAP_SIZE_ELEM      ("MaximumMapSize");

namespace MapGenerator
{
    // GENERATION
    void generate(Map&               o_Map,
                  const std::string& i_MapConfigFile = DEFAULT_MAP_CONFIG);

    // GENERATION (private functions)
    unsigned int parseMapDimension(const rapidjson::Value& i_Elem,
                                   const std::string&      i_SubElemName);
    void placeBorder(const rapidjson::Value& i_BorderElem, 
                     const std::string&      i_SideName);
    void fillBiomeRegion(Biome i_Biome, Coord i_ULCorner, Coord i_LRCorner);
    void executePhase(const rapidjson::Value& i_PhaseElem, 
                      const std::string       i_PhaseName);
    void executePhaseForElement(Biome                         i_Element,
                                const std::list<Constraint*>& i_Constraints,
                                const std::string             i_PhaseName,
                                unsigned int                  i_ElemQty,
                                unsigned int                  i_MaxTries);
    unsigned int parsePhaseQtyElem(const rapidjson::Value& i_PhaseElem);
    void runOverpass();
    void removeLonelyTiles(const Biome& i_ChangedBiome, 
                           const Coord& i_ReadCoord);
    const Coord randCoord();
};