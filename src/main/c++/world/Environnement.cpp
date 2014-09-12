#include "Environnement.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Environnement::Environnement(EnvType type)
{
	this->type = type;
	this->orientation = Direction(nextRand(3));
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                  GETTERS                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

EnvType Environnement::getType() const
{
	return type;
}

Direction Environnement::getOrientation() const
{
	return orientation;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   STATUS                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

bool Environnement::isSolidLand() const
{
	return type != LAKE && type != OCEAN;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                    ASSET                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

Asset Environnement::assetFile() const
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

const char* Environnement::toString() const
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