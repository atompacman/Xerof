#include "AtomAI.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

AtomAI::AtomAI(Civilization* civ) : AI(civ) {}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                  MOVE HUMAN                 //
//- - - - - - - - - - - - - - - - - - - - - - -//

Order AtomAI::giveOrderToHuman(Human& human)
{
	while (human.getEnvironnementInFront() == OCEAN) {
		human.position.facingDirection = Direction((nextRand(8)) % 8);
	}
	return Order(WALK, human.position.facingDirection);
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   HELPERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

void AtomAI::printSurroundingTiles(const Human& human) 
{
	const Tile*** tiles = human.getSurroundingTiles();
	int zoneLength = human.getRangeOfSight() * 2 + 1;

	for (int y = 0; y < zoneLength; ++y) {
		for (int x = 0; x < zoneLength; ++x) {
			const char* name = tiles[x][y]->getEnvironnement()->toString();
			fprintf(stdout, "%-10s   ", name);
		}
		fprintf(stdout, "\n");
	}
}