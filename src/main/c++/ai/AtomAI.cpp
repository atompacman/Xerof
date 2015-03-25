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

Order AtomAI::giveOrder(Human& i_Human)
{
    while (i_Human.getEnvironnementInFront() == OCEAN) {
        i_Human.m_Pos.m_FacingDir = Direction((nextRand(8)) % 8);
	}
    return Order(WALK, i_Human.m_Pos.m_FacingDir);
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
            LOG(TRACE) << std::setw(10) << name << "  ";
		}
		LOG(TRACE) << '\n';
	}
}