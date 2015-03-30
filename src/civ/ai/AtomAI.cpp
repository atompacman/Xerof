#include "AtomAI.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                GIVE ORDER                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Order AtomAI::giveOrder(const Human& i_Human)
{
    UINT attempts(0);
    Direction dir(i_Human.getPos().m_Dir);
    while (!i_Human.getTileInDir(dir).isPassable() && attempts < 100) {
        dir = randDirNoCenter();
        ++attempts;
    }
    return Order(WALK, dir);
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
            EnvType type = tiles[x][y]->getEnvironment().getType();
            LOG(TRACE) << std::setw(10) << ENV_NAMES[type] << "  ";
		}
		LOG(TRACE) << '\n';
	}
}