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
	assert(population < MAX_POPULATION);
	assert(World::getInstance()->map->getTile(i_Pos)->isPassable());

	people[population] = new Human(Position(UP, i_Pos));
	++population;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Human* CivController::getHuman(UINT i_ID)
{
    assert(i_ID < population);
    return people[i_ID];
}