#include <Individual.h>
#include <Map.h>
#include <Tile.h>
#include <WorldPerception.h>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

WorldPerception::WorldPerception(const Individual& i_Info, const Map& i_Map) :
m_Info(i_Info),
m_Map(i_Map)
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Position& WorldPerception::getPosition() const
{
    return m_Info.getPosition();
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                 SURROUNDINGS                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool WorldPerception::isWithinMapLimits(Direction i_Dir) const
{
    return incrementedToDirection(m_Info.m_Pos.tileCoord(), i_Dir) 
        < m_Map.dimensions();
}

const Tile& WorldPerception::getTileInDir(Direction i_Dir) const
{
    return m_Map(incrementedToDirection(m_Info.m_Pos.tileCoord(), i_Dir));
}

const Tile& WorldPerception::getTileInFront() const
{
    return getTileInDir(m_Info.m_Pos.facingDir());
}

Biome WorldPerception::getBiomeInFront() const
{
    return getTileInFront().getEnvironment().getBiome();
}
