#include "CivController.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

CivController::CivController(): Civilization() {}


//= = = = = = = = = = = = = = = = = = = = = = =//
//              DAWN OF CIVILIZATION           //
//- - - - - - - - - - - - - - - - - - - - - - -//

void CivController::placeFirstHuman()
{
	Map* map = World::getInstance()->map;

	Coord<int> startLoc;

	do {
		startLoc = randTile();
	} while (!map->getTile(startLoc)->isPassable());

	addHuman(startLoc);
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                     ADD                     //
//- - - - - - - - - - - - - - - - - - - - - - -//

void CivController::addHuman(Coord<int> coord)
{
	assert(population < MAX_POPULATION);
	assert(World::getInstance()->map->getTile(coord)->isPassable());

	people[population] = new Human(Position(UP, coord));
	++population;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   GETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

Human* CivController::getHumanPtr(unsigned int id)
{
	assert(id < population);
	return people[id];
}