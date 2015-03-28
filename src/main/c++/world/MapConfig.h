#pragma once
#include "rapidjson\document.h"
#include "rapidjson\error\en.h"
#include "..\utils\Elem2D.h"
#include "Environment.h"
#include "..\utils\JSONUtils.h"
#include "LandTypePropotions.h"

// The default map configuration file
static const char* DEFAULT_MAP_CONFIG   = "map/DefaultConfig.json";

// JSON file elements
static const char* ROOT_ELEM            = "XerofMapConfig";
static const char* DIM_ELEM             = "MapDimensions";
static const char* DIM_WIDTH_SUB_ELEM   = "width";
static const char* DIM_HEIGHT_SUB_ELEM  = "height";
static const char* LAND_PROPOR_ELEM     = "LandProportion";
static const char* LAND_DISPERS_ELEM    = "LandDispertion";
static const char* LAND_COMPACT_ELEM    = "LandCompactness";
static const char* TUNDRA_TRANS_W_ELEM  = "TundraTransitionWidth";
static const char* OCEAN_BORDERS_W_ELEM = "OceanBordersWidth";
static const char* ROCKY_BORDERS_W_ELE  = "RockyZonesThickness";
static const char* TOTAL_LAND_PROP_ELEM = "TotalLandTypeProportions";
static const char* INIT_LAND_PROP_ELEM  = "InitialSeedLandTypeProportions";

class MapConfig
{
public:
    Dimensions      m_Dim;
    double          m_LandProp;
    double          m_LandDispertion;
    double          m_LandCompactness;
    UINT            m_RandTundraWidth;
    UINT            m_OceanBorderWidth;
    UINT            m_RockyZoneThickn;
    LandProportions m_TotalProp;
    LandProportions m_InitProp;

    // CONSTRUCTOR/DESTRUCTOR
    MapConfig();
    MapConfig(const char* i_ParamFile);
};