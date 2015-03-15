#pragma once
#include "..\civilization\Position.h"
#include "..\utils\Random.h"
#include "MapElement.h"

enum EnvType
{
	GRASSLAND, LAKE, OCEAN, PLAIN, ROCKY, TUNDRA
};

class Environment: public MapElement
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	Environment(EnvType type);
	
	// GETTERS
	EnvType getType() const;
	Direction getOrientation() const;

	// STATUS
	bool isSolidLand() const;

	// ASSET
	Asset assetFile() const;

	// OTHER
	const char* toString() const;

private:
	EnvType type;
	Direction orientation;
};