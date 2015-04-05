#include "HumanInfo.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

HumanInfo::HumanInfo(const Position& i_StartingPos) :
m_Pos(i_StartingPos),
m_IsReady(true),
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


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     STATE                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool HumanInfo::isReady() const
{
    return m_IsReady;
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