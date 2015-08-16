#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include "rapidjson\document.h"
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <map>
#include <vector>
/*============================================================================//
| Represents an element from the "Phases" element of the map config file
|-----------------------------------------------------------------------------||
| int bobby;
\=============================================================================*/

using namespace rapidjson;

enum  Biome;
class Constraint;
class Map;

typedef std::map<Biome,std::pair<size_t,std::vector<Constraint*>>> Constraints;

#define QTY_ELEM            "Quantity"
#define RELATIVE_ELEM       "Relative"
#define ABSOLUTE_ELEM       "Absolute"
#define ENV_TYPES_PROP_ELEM "EnvTypesProportions"
#define CONSTRAINTS_ELEM    "Constraints"
#define MAX_TRIES_ELEM      "MaxNumTriesBeforeSkipping"
#define STRENGTH_ELEM       "Strength"
#define MIN_ELEM            "Min"
#define MAX_ELEM            "Max"
#define RADIUS_ELEM         "Radius"

struct Phase
{
    const char*  m_Name;
    Constraints  m_Cnstrts;
    unsigned int m_MaxTries;

    // CONSTRUCTOR/DESTRUCTOR
    Phase(const Map&              i_Map, 
          const char*             i_Name, 
          const rapidjson::Value& i_JSONElem);

    ~Phase();

private:
    // CONSTRUCTOR/DESTRUCTOR
    unsigned int parseQuantityElem(const rapidjson::Value& i_QtyElem, 
                                   unsigned int            i_Area);

    void parseEnvTypeProps(const rapidjson::Value& i_EnvPropElem, 
                           unsigned int            qty);

    void parseCnstrts(const rapidjson::Value& i_CnstrtElem, 
                      const Map&              i_Map);
};
