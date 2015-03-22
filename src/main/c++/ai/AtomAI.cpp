#include "AtomAI.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

AtomAI::AtomAI(Civilization* i_Civ) : 
AI(i_Civ) 
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                GIVE ORDER                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Order AtomAI::giveOrder(const Human& i_Human)
{
    int direction;
    while (i_Human.getEnvironnementInFront() == OCEAN) {
        direction = Direction((nextRand(8)) % 8);
	}
    return Order(WALK, direction);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                  HELPERS                                   //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void AtomAI::printSurroundingTiles(const Human& i_Human)
{
    const Tile*** tiles = i_Human.getSurroundingTiles();
    int zoneLength = i_Human.getRangeOfSight() * 2 + 1;

	for (int y = 0; y < zoneLength; ++y) {
		for (int x = 0; x < zoneLength; ++x) {
			const char* name = tiles[x][y]->getEnvironment()->toString();
			LOG_TRACE_F("%-10s   ", name);
		}
		LOG(TRACE) << '\n';
	}
}