#include "Environment.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Environment::Environment(EnvType type)
{
	this->type = type;
	this->orientation = Direction(nextRand(3));
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                  GETTERS                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

EnvType Environment::getType() const
{
	return type;
}

Direction Environment::getOrientation() const
{
	return orientation;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   STATUS                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

bool Environment::isSolidLand() const
{
	return type != LAKE && type != OCEAN;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                    ASSET                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

Asset Environment::assetFile() const
{
	switch (type) {
	case GRASSLAND: return GRASSLAND_TILE_FILE;
	case OCEAN:		return OCEAN_TILE_FILE;
	case PLAIN:		return PLAINS_TILE_FILE;
	case ROCKY:		return ROCKY_TILE_FILE;
	case TUNDRA:	return TUNDRA_TILE_FILE;
	}
	return SELECTION;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                    OTHER                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

const char* Environment::toString() const
{
	switch (type) {
	case GRASSLAND: return "GRASSLAND";
	case OCEAN:		return "OCEAN";
	case PLAIN:		return "PLAIN";
	case ROCKY:		return "ROCKY";
	case TUNDRA:	return "TUNDRA";
	}
	return "???";
}