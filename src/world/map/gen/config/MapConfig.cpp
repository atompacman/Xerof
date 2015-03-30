#include "MapConfig.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

MapConfig::MapConfig() :
MapConfig(DEFAULT_MAP_CONFIG)
{}

MapConfig::MapConfig(const char* i_ParamFile)
{
    // Parse config file
    rapidjson::Document o_Doc;
    rapidjson::Value& root = parseJSON(o_Doc, i_ParamFile, CONFIG_ROOT_ELEM);

    // Read map dimensions
    UINT width  = readMapSizeElem(root, DIM_WIDTH_SUB_ELEM);
    UINT height = readMapSizeElem(root, DIM_HEIGHT_SUB_ELEM);
    m_Dim = Dimensions(width, height);

    // Read simple parameters
    m_LandProp        = getNormDouble(root, LAND_PROPOR_ELEM);
    m_InitProp        = getNormDouble(root, INIT_LAND_PROP_ELEM);
    m_LandDispertion  = getDouble(root, LAND_DISPERS_ELEM);
    m_LandCompactness = getDouble(root, LAND_COMPACT_ELEM);

    // Read random tundra width
    m_RandTundraWidth = getUINT(root, TUNDRA_TRANS_W_ELEM);
    if (m_RandTundraWidth > height * 0.5) {
        FatalErrorDialog("Random tundra width cannot be \
            greater than half of map height");
    }

    // Read ocean border width
    m_OceanBorderWidth = getUINT(root, OCEAN_BORDERS_W_ELEM);
    if (m_OceanBorderWidth > width * 0.5 || m_OceanBorderWidth > height * 0.5) {
        FatalErrorDialog("Ocean border width cannot be \
            greater than half of map width/height");
    }

    // Read rocky zone thickness
    m_RockyZoneThickn = getUINT(root, ROCKY_BORDERS_W_ELE);

    // Read land type proportions
    m_LandTypeProp=LandProportions(getSubElem(root, TOTAL_LAND_TYPE_PROP_ELEM));
    m_InitLandProp=LandProportions(getSubElem(root, INIT_LAND_TYPE_PROP_ELEM));
}

UINT MapConfig::readMapSizeElem(const Value& i_Root, const char* i_Elem)
{
    UINT size = getUINT(getSubElem(i_Root, DIM_ELEM), i_Elem);
    if (size < s_ConfigLimits.m_MinMapSize) {
        std::stringstream ss;
        ss << "Map " << i_Elem << " cannot be lower than " 
            << s_ConfigLimits.m_MinMapSize;
        FatalErrorDialog(ss.str());
    }
    if (size > s_ConfigLimits.m_MaxMapSize) {
        std::stringstream ss;
        ss << "Map " << i_Elem << " cannot be higher than "
            << s_ConfigLimits.m_MinMapSize;
        FatalErrorDialog(ss.str());
    }
    return size;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                         LOAD CONFIGURATION LIMITS                          //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const MapConfig::Limits MapConfig::s_ConfigLimits(loadConfigLimits());

MapConfig::Limits MapConfig::loadConfigLimits()
{
    // Parse config file
    rapidjson::Document o_Doc;
    rapidjson::Value& root = parseJSON(o_Doc, MAP_LIMITS, LIMITS_ROOT_ELEM);
    Limits limits;

    // Read maximum map size parameters
    limits.m_MinMapSize = getUINT(root, MIN_MAP_SIZE_ELEM);
    limits.m_MaxMapSize = getUINT(root, MAX_MAP_SIZE_ELEM);

    return limits;
}