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

enum EnvType
{
    GRASSLAND,
    LAKE,
    OCEAN,
    PLAIN,
    ROCKY,
    TUNDRA
};

static const std::map<std::string, EnvType> ENV_TYPES = {
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

    // SETTERS
    void setEnvType(EnvType i_Type);

	// STATUS
	bool isSolidLand() const;
    static bool isSolidLand(EnvType i_Type);

	// ASSET
	AssetID assetFile() const;

private:
	EnvType   m_Type;
	Direction m_Orien;
};