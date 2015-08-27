#pragma once

#include <rapidjson\document.h>

/*============================================================================\\
| Shortcuts for JSON value verification and extraction
|-----------------------------------------------------------------------------||
| - JSON file parsing
| - Node extraction
\=============================================================================*/

enum Biome;

rapidjson::Value& parseJSON(rapidjson::Document& o_Doc,
                            const std::string&   i_JSONFile,
                            const std::string&   i_RootElemName);

const rapidjson::Value& parseSubElem   (const rapidjson::Value& i_Value,
                                        const std::string&      i_Elem);
unsigned int            parseUINT      (const rapidjson::Value& i_Value,
                                        const std::string&      i_Elem);
double                  parseDouble    (const rapidjson::Value& i_Value,
                                        const std::string&      i_Elem);
double                  parseNormDouble(const rapidjson::Value& i_Value,
                                        const std::string&      i_Elem);
const std::string       parseString    (const rapidjson::Value& i_Value,
                                        const std::string&      i_Elem);
Biome                   parseBiome     (const rapidjson::Value& i_Value,
                                        const std::string&      i_Elem);
