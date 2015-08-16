#pragma once

#include <assert.h>
#include <Border.h>
#include <Elem2D.h>
#include <list>
#include <Phase.h>
#include <rapidjson\document.h>

/*============================================================================\\
| MAP CONFIG FILE REPRESENTATION
|-----------------------------------------------------------------------------||
| Represents the content of a map generation configuration file.
\=============================================================================*/

// JSON configuration file elements
#define CONFIG_ROOT_ELEM    "XerofMapGeneratorConfig"
#define DIM_ELEM            "Dimensions"
#define DIM_WIDTH_SUB_ELEM  "Width"
#define DIM_HEIGHT_SUB_ELEM "Height"
#define INIT_LAND_TYPE_ELEM "InitialEnvType"
#define BORDERS_ELEM        "Borders"
#define PHASES_ELEM         "Phases"

// JSON configurations limits file elements
#define LIMITS_ROOT_ELEM    "XerofMapConfigLimits"
#define MIN_MAP_SIZE_ELEM   "MinimumMapSize"
#define MAX_MAP_SIZE_ELEM   "MaximumMapSize"

struct Limits
{
    unsigned int m_MinMapSize;
    unsigned int m_MaxMapSize;
};

class MapConfig
{
public:
    Dimensions        m_Dim;
    Biome             m_InitEnvType;
    std::list<Border> m_Borders;
    std::list<Phase>  m_Phases;

    // CONSTRUCTOR/DESTRUCTOR
    MapConfig(const char* i_ParamFile);
    void buildConstraints(const Map& i_Map);

private:
    // Temporary
    rapidjson::Document m_Doc;

    // LOAD CONFIGURATION LIMITS
    static const Limits s_ConfigLimits;
    static Limits loadConfigLimits();
};

