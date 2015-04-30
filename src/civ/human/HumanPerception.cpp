#include "HumanPerception.h"

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

const HumanInfo& HumanPerception::infos() const
{
    return m_Info;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                 SURROUNDINGS                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool HumanPerception::isWithinMapLimits(Direction i_Dir) const
{
	return incrementedToDirection(m_Info.m_Pos.tileCoord(),i_Dir) < m_Map.dim();
}

const Tile& HumanPerception::getTileInDir(Direction i_Dir) const
{
    return m_Map.getTile(incrementedToDirection(
        m_Info.m_Pos.tileCoord(), i_Dir));
}

const Tile& HumanPerception::getTileInFront() const
{
    return getTileInDir(m_Info.m_Pos.facingDir());
}

EnvType HumanPerception::getEnvInFront() const
{
    return getTileInFront().getEnvironment().getType();
}