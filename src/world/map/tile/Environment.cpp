#include <Assets.h>
#include <Environment.h>
#include <Random.h>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Environment::Environment(Biome i_Type) :
m_Biome(i_Type),
m_Dispo()
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Biome Environment::getBiome() const
{
    return m_Biome;
}

Disposition Environment::getDisposition() const
{
    return m_Dispo;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   SETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Environment::setBiome(Biome i_Biome)
{
    m_Biome = i_Biome;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    STATUS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Environment::isSolidLand() const
{
    return isSolidLand(m_Biome);
}

bool Environment::isSolidLand(Biome i_Biome)
{
    return i_Biome != LAKE && i_Biome != OCEAN;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     ASSET                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

AssetID Environment::assetFile() const
{
    switch (m_Biome) {
    case GRASSLAND: return BIOME_GRASSLAND;
    case OCEAN:     return BIOME_OCEAN;
    case PLAIN:     return BIOME_PLAINS;
    case ROCKY:     return BIOME_ROCKY;
    case TUNDRA:    return BIOME_TUNDRA;
    }
    return SELECTION;
}