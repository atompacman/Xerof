#include "Environment.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Environment::Environment(Biome i_Type) :
m_Type(i_Type),
m_Orien(randBasicDir())
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Biome Environment::getBiome() const
{
    return m_Type;
}

Direction Environment::getOrientation() const
{
    return m_Orien;
}



//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   SETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Environment::setBiome(Biome i_Type)
{
    m_Type = i_Type;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    STATUS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Environment::isSolidLand() const
{
    return isSolidLand(m_Type);
}

bool Environment::isSolidLand(Biome i_Type)
{
    return i_Type != LAKE && i_Type != OCEAN;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     ASSET                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

AssetID Environment::assetFile() const
{
    switch (m_Type) {
    case GRASSLAND: return GRASSLAND_TILE_FILE;
    case OCEAN:		return OCEAN_TILE_FILE;
    case PLAIN:		return PLAINS_TILE_FILE;
    case ROCKY:		return ROCKY_TILE_FILE;
    case TUNDRA:	return TUNDRA_TILE_FILE;
    }
    return SELECTION;
}