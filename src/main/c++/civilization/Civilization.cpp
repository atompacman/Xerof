#include "Civilization.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Civilization::Civilization(const Map& i_Map) :
m_People(),
m_Map(i_Map)
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Human& Civilization::getHuman(UINT i_ID) const
{
    return m_People.at(i_ID);
}

Human& Civilization::getHuman(UINT i_ID)
{
    return m_People.at(i_ID);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     ADD                                    //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Civilization::addHuman(Coord i_Pos)
{
    assert(m_People.size() < CIV_MAX_POP);
    assert(m_Map.getTile(i_Pos).isPassable());
    m_People.push_back(Human(Position(i_Pos), m_Map));
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    STATUS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

UINT Civilization::population() const
{
    return m_People.size();
}