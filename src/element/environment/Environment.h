#pragma once

#include <Assets.h>
#include <Direction.h>
#include <GraphicalElement.h>
#include <map>
#include <string>

/*============================================================================||
| Wrapper around a biome type
|-----------------------------------------------------------------------------||
| Class hierarchy:
| GraphicalElement -> Environment
|
| Links an abstract environment type to a physical asset that has an orientation
| that is random.
\=============================================================================*/

enum Biome
{
    GRASSLAND,
    OCEAN,
    PLAIN,
    ROCKY,
    TUNDRA
};

static const char* ENV_NAMES[] = {
    "GRASSLAND",
    "OCEAN",
    "PLAIN",
    "ROCKY",
    "TUNDRA"
};

static const std::map<std::string, Biome> STR_TO_BIOME = {
    { "GRASSLAND", GRASSLAND },
    { "OCEAN",     OCEAN },
    { "PLAIN",     PLAIN },
    { "ROCKY",     ROCKY },
    { "TUNDRA",    TUNDRA }
};

static const std::map<Biome, AssetID> BIOME_TO_ASSET = {
    { GRASSLAND, BIOME_GRASSLAND },
    { OCEAN,     BIOME_OCEAN },
    { PLAIN,     BIOME_PLAINS },
    { ROCKY,     BIOME_ROCKY },
    { TUNDRA,    BIOME_TUNDRA }
};

class Environment : public GraphicalElement
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Environment(Biome i_Biome) :
        GraphicalElement(BIOME_TO_ASSET.at(i_Biome)),
        m_Biome(i_Biome),
        m_Disposition()
    {}

    // GETTERS
    Biome       getBiome() const       { return m_Biome; }
    Disposition getDisposition() const { return m_Disposition; }

    // SETTERS
    void        setBiome(Biome i_Biome) { m_Biome = i_Biome;
                                          m_AssetID=BIOME_TO_ASSET.at(i_Biome);}

    // STATUS
    bool        isSolidLand() const        { return isSolidLand(m_Biome); }
    static bool isSolidLand(Biome i_Biome) { return i_Biome != OCEAN; }

private:
    Biome       m_Biome;
    Disposition m_Disposition;
};
