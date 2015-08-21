#pragma once

#include <Direction.h>
#include <list>
#include <map>
#include <MapElement.h>
#include <string>

/*============================================================================||
| Wrapper around an environment type
|-----------------------------------------------------------------------------||
| Links an abstract environment type to a physical asset that has an orientation
| that is random.
\=============================================================================*/

enum AssetID;

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
    Biome       getBiome() const;
    Disposition getDisposition() const;

    // SETTERS
    void setBiome(Biome i_Type);

    // STATUS
    bool        isSolidLand() const;
    static bool isSolidLand(Biome i_Type);

    // ASSET
    AssetID assetFile() const;

private:
    Biome       m_Biome;
    Disposition m_Dispo;
};