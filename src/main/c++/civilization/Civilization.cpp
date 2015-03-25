#include "Civilization.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Civilization::Civilization()
{
	m_People = new Human*[MAX_POPULATION];
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Human& Civilization::getHuman(UINT i_ID) const
{
    assert(i_ID < m_Pop);
    return *m_People[i_ID];
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    STATUS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

UINT Civilization::getPopulation() const
{
	return m_Pop;
}