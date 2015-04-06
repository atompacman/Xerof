#include "HumanInfo.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

HumanInfo::HumanInfo(const Position& i_StartingPos) :
m_Pos(i_StartingPos),
m_IsReady(true),
m_IsSelected(false),
m_MoveSpeed(1),
m_ROSight(2)
{}


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
//                                     STATS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

float HumanInfo::getMoveSpeed() const
{
    return m_MoveSpeed;
}

UINT HumanInfo::getRangeOfSight() const
{
    return m_ROSight;
}