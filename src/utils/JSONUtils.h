#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include "rapidjson\document.h"
/*============================================================================||
| Shortcuts for JSON value verification and extraction
|-----------------------------------------------------------------------------||
| - JSON file parsing
| - Node extraction
\=============================================================================*/

enum Biome;

#define ENV_TYPE_ELEM "EnvType"

rapidjson::Value& parseJSON (rapidjson::Document& o_Doc,
                             const char*          i_JSONFile,
                             const char*          i_RootElemName);

const rapidjson::Value& parseSubElem   (const rapidjson::Value& i_Value,
                                        const char*             i_Elem);
unsigned int            parseUINT      (const rapidjson::Value& i_Value,
                                        const char*             i_Elem);
double                  parseDouble    (const rapidjson::Value& i_Value,
                                        const char*             i_Elem);
double                  parseNormDouble(const rapidjson::Value& i_Value,
                                        const char*             i_Elem);
const char*             parseString    (const rapidjson::Value& i_Value,
                                        const char*             i_Elem);
Biome                   parseEnvType   (const rapidjson::Value& i_Value,
                                        const char*             i_Elem);
Biome                   parseEnvType   (const rapidjson::Value& i_Value);