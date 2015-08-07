#include "HumanInfo.h"
#include <iosfwd>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

HumanInfo::HumanInfo(const Position& i_StartingPos, Dimensions i_MapDim) :
m_Pos(i_StartingPos),
m_IsReady(true),
m_IsSelected(false),
m_MoveSpeed(1),
m_ROS(NULL),
m_MapKnow(i_MapDim)
{
    m_ROS = new RangeOfSight(std::ifstream("config/range_of_sight/90degre.ros"));
    discoverSurroundingTiles();
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Position& HumanInfo::getPos() const
{
    return m_Pos;
}

Position& HumanInfo::getPos()
{
    return m_Pos;
}

const MapKnowledge& HumanInfo::getMapKnowledge() const
{
    return m_MapKnow;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   SETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void HumanInfo::setReady()
{
    m_IsReady = true;
}

void HumanInfo::setBusy()
{
    m_IsReady = false;
}

void HumanInfo::select()
{
    m_IsSelected = true;
}

void HumanInfo::unselect()
{
    m_IsSelected = false;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     STATE                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool HumanInfo::isReady() const
{
    return m_IsReady;
}

bool HumanInfo::isSelected() const
{
    return m_IsSelected;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                            DISCOVER SURROUNDING TILES                      //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void HumanInfo::discoverSurroundingTiles()
{
    m_MapKnow.discover(m_Pos, *m_ROS);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     STATS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

float HumanInfo::getMoveSpeed() const
{
    return m_MoveSpeed;
}