#include "Civilization.h"
#include "..\world\map\Map.h"
#include "..\Parameters.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Civilization::Civilization() :
m_People()
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const HumanInfo& Civilization::getHuman(unsigned int i_ID) const
{
    return m_People.at(i_ID);
}

HumanInfo& Civilization::getHuman(unsigned int i_ID)
{
    return m_People.at(i_ID);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    STATUS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

unsigned int Civilization::population() const
{
    return m_People.size();
}