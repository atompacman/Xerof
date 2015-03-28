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
    rapidjson::Value& root = parseJSON(o_Doc, i_ParamFile, ROOT_ELEM);

    // Read map dimensions
    UINT width  = getUINT(getSubElem(root, DIM_ELEM), DIM_WIDTH_SUB_ELEM);
    UINT height = getUINT(getSubElem(root, DIM_ELEM), DIM_HEIGHT_SUB_ELEM);
    m_Dim = Dimensions(width, height);

    // Read simple parameters
    m_LandProp          = getNormDouble(root, LAND_PROPOR_ELEM);
    m_LandDispertion    = getNormDouble(root, LAND_DISPERS_ELEM);
    m_LandCompactness   = getNormDouble(root, LAND_COMPACT_ELEM);
    m_RandTundraWidth   = getUINT      (root, TUNDRA_TRANS_W_ELEM);
    m_OceanBorderWidth  = getUINT      (root, OCEAN_BORDERS_W_ELEM);
    m_RockyZoneThickn   = getUINT      (root, ROCKY_BORDERS_W_ELE);

    // Read land proportions parameters
    m_TotalProp = LandProportions(getSubElem(root, TOTAL_LAND_PROP_ELEM));
    m_InitProp  = LandProportions(getSubElem(root, INIT_LAND_PROP_ELEM));
}