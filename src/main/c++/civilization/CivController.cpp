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
	Coord<int> startLoc;
	do {
		startLoc = randTile();
    } while (!World::getInstance()->map->getTile(startLoc)->isPassable());

	addHuman(startLoc);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     ADD                                    //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void CivController::addHuman(Coord<int> i_Pos)
{
	assert(m_Pop < MAX_POPULATION);
	assert(World::getInstance()->map->getTile(i_Pos)->isPassable());

	m_People[m_Pop] = new Human(Position(UP, i_Pos));
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