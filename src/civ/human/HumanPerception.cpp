#include <HumanInfo.h>
#include <HumanPerception.h>
#include <Map.h>
#include <Tile.h>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

HumanPerception::HumanPerception(const HumanInfo& i_Info, const Map& i_Map) :
m_Info(i_Info),
m_Map(i_Map)
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Position& HumanPerception::getPosition() const
{
    return m_Info.getPosition();
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                 SURROUNDINGS                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool HumanPerception::isWithinMapLimits(Direction i_Dir) const
{
    return incrementedToDirection(m_Info.m_Pos.tileCoord(), i_Dir) 
        < m_Map.dimensions();
}

const Tile& HumanPerception::getTileInDir(Direction i_Dir) const
{
    return m_Map(incrementedToDirection(m_Info.m_Pos.tileCoord(), i_Dir));
}

const Tile& HumanPerception::getTileInFront() const
{
    return getTileInDir(m_Info.m_Pos.facingDir());
}

Biome HumanPerception::getBiomeInFront() const
{
    return getTileInFront().getEnvironment().getBiome();
}
