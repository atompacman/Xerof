#pragma once
#include <list>
#include "MapElement.h"
#include "..\civilization\Position.h"
#include "..\utils\Random.h"

enum EnvType
{
    GRASSLAND,
    LAKE,
    OCEAN,
    PLAIN,
    ROCKY,
    TUNDRA
};

static const std::map<const char*, EnvType> ENV_TYPES = {
    { "GRASSLAND",  GRASSLAND   },
    { "LAKE",       LAKE        },
    { "OCEAN",      OCEAN       },
    { "PLAIN",      PLAIN       },
    { "ROCKY",      ROCKY       },
    { "TUNDRA",     TUNDRA      }
};

static const char* ENV_NAMES[] = {
    "GRASSLAND",
    "LAKE",
    "OCEAN",
    "PLAIN",
    "ROCKY",
    "TUNDRA"
};

static const std::list<EnvType> LAND_ENV_TYPES = {
    GRASSLAND,
    PLAIN,
    ROCKY,
    TUNDRA
};

class Environment : public MapElement
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    Environment(EnvType i_Type);
	
	// GETTERS
	EnvType getType() const;
	Direction getOrientation() const;

	// STATUS
	bool isSolidLand() const;
    static bool isSolidLand(EnvType i_Type);

	// ASSET
	AssetID assetFile() const;

	// OTHER
	const char* toString() const;

private:
	EnvType   m_Type;
	Direction m_Orien;
};