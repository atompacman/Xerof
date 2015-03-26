#include "CivController.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

CivController::CivController(): 
Civilization() 
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                            DAWN OF CIVILIZATION                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //


void CivController::placeFirstHuman()
{
	Coord startLoc;
	do {
		startLoc = randTile();
    } while (!World::getInstance()->m_Map->getTile(startLoc)->isPassable());

	addHuman(startLoc);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     ADD                                    //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void CivController::addHuman(Coord i_Pos)
{
	assert(m_Pop < MAX_POPULATION);
	assert(World::getInstance()->m_Map->getTile(i_Pos)->isPassable());

    m_People[m_Pop] = new Human(Position(i_Pos, UP));
	++m_Pop;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Human* CivController::getHuman(UINT i_ID)
{
    assert(i_ID < m_Pop);
    return m_People[i_ID];
}