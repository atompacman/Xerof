#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <list>
#include <string>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\src\engine\Assets.h"
#include "MapElement.h"
#include "..\src\utils\Random.h"
/*============================================================================||
| Wrapper around an environment type
|-----------------------------------------------------------------------------||
| Links an abstract environment type to a physical asset that has an orientation
| that is random.
\=============================================================================*/

enum Biome
{
    GRASSLAND,
    LAKE,
    OCEAN,
    PLAIN,
    ROCKY,
    TUNDRA
};

static const std::map<std::string, Biome> ENV_TYPES = {
    { "GRASSLAND", GRASSLAND },
    { "LAKE",      LAKE },
    { "OCEAN",     OCEAN },
    { "PLAIN",     PLAIN },
    { "ROCKY",     ROCKY },
    { "TUNDRA",    TUNDRA }
};

static const char* ENV_NAMES[] = {
    "GRASSLAND",
    "LAKE",
    "OCEAN",
    "PLAIN",
    "ROCKY",
    "TUNDRA"
};

static const std::list<Biome> LAND_ENV_TYPES = {
    GRASSLAND,
    PLAIN,
    ROCKY,
    TUNDRA
};

class Environment : public MapElement
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Environment(Biome i_Type);

    // GETTERS
    Biome     getBiome() const;
    Direction getOrientation() const;

    // SETTERS
    void setBiome(Biome i_Type);

    // STATUS
    bool        isSolidLand() const;
    static bool isSolidLand(Biome i_Type);

    // ASSET
    AssetID assetFile() const;

private:
    Biome    m_Type;
    Direction m_Orien;
};