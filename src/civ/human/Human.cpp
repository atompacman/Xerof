#include "Human.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Human::Human(const Position& i_StartingPos, const Map& i_Map) :
m_Pos(i_StartingPos),
m_IsReady(true),
m_MoveSpeed(1),
m_ROSight(2),

m_Map(i_Map)
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Position& Human::getPos() const
{
    return m_Pos;
}

Position& Human::getPos()
{
    return m_Pos;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                 SURROUNDINGS                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Tile*** const Human::getSurroundingTiles() const
{
    Coord lowerLeft (max(0, m_Pos.m_Coord.x - m_ROSight), 
                     max(0, m_Pos.m_Coord.y - m_ROSight));
    Coord upperRight(min(m_Pos.m_Coord.x - m_ROSight, m_Map.dim().x - 1),
                     min(m_Pos.m_Coord.y - m_ROSight, m_Map.dim().y - 1));
    return m_Map.getTiles(lowerLeft, upperRight);
}

const Tile& Human::getTileInDir(Direction i_Dir) const
{
    return m_Map.getTile(incrementedToDirection(m_Pos.tileCoord(), i_Dir));
}

const Tile& Human::getTileInFront() const
{
    return getTileInDir(m_Pos.m_Dir);
}

EnvType Human::getEnvInFront() const
{
    return getTileInFront().getEnvironment().getType();
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   SETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Human::setReady()
{
    m_IsReady = true;
}

void Human::setBusy()
{
    m_IsReady = false;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     STATE                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Human::isReady() const
{
    return m_IsReady;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     STATS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

float Human::getMoveSpeed() const
{
	return m_MoveSpeed;
}

UINT Human::getRangeOfSight() const
{
	return m_ROSight;
}