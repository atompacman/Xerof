#include <map>
#include <MapConfig.h>
#include <Parameters.h>
#include <rapidjson\error\en.h>

const Limits MapConfig::s_ConfigLimits = loadConfigLimits();

using namespace rapidjson;

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

MapConfig::MapConfig(const char* i_ParamFile)
{
    Value& root = parseJSON(m_Doc, i_ParamFile, CONFIG_ROOT_ELEM);

    // Parse map dimensions
    const Value& elem(parseSubElem(root, DIM_ELEM));
    unsigned int width(parseUINT(elem, DIM_WIDTH_SUB_ELEM));
    if (width < s_ConfigLimits.m_MinMapSize) {
        FatalErrorDialog("Map width is too small");
    }
    if (width > s_ConfigLimits.m_MaxMapSize) {
        FatalErrorDialog("Map width is too large");
    }
    unsigned int height(parseUINT(elem, DIM_HEIGHT_SUB_ELEM));
    if (height < s_ConfigLimits.m_MinMapSize) {
        FatalErrorDialog("Map height is too small");
    }
    if (height > s_ConfigLimits.m_MaxMapSize) {
        FatalErrorDialog("Map height is too large");
    }
    m_Dim = Dimensions(width, height);

    // Parse init env type
    m_InitEnvType = parseEnvType(root, INIT_LAND_TYPE_ELEM);

    // Parse borders
    const Value& bordersElem(parseSubElem(root, BORDERS_ELEM));
    auto it(bordersElem.MemberBegin());
    for (; it != bordersElem.MemberEnd(); ++it) {
        m_Borders.emplace_back(it->name.GetString(), bordersElem);
    }
}

void MapConfig::buildConstraints(const Map& i_Map)
{
    // Parse phases
    const Value& phaseElem(parseSubElem(m_Doc[CONFIG_ROOT_ELEM], PHASES_ELEM));
    auto it = phaseElem.MemberBegin();
    for (; it != phaseElem.MemberEnd(); ++it) {
        m_Phases.emplace_back(i_Map, it->name.GetString(), it->value);
    }
}

Limits MapConfig::loadConfigLimits()
{
    // Parse config file
    Document doc;
    Value& root = parseJSON(doc, MAP_LIMITS, LIMITS_ROOT_ELEM);
    Limits limits;

    // Read maximum map size parameters
    limits.m_MinMapSize = parseUINT(root, MIN_MAP_SIZE_ELEM);
    limits.m_MaxMapSize = parseUINT(root, MAX_MAP_SIZE_ELEM);

    return limits;
}