#include "AtomAI.h"
#include "..\..\utils\Direction.h"
#include "..\human\HumanPerception.h"
#include "Order.h"
#include "..\human\Position.h"
#include "..\..\utils\Random.h"
#include "..\..\world\map\tile\Tile.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                GIVE ORDER                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Order AtomAI::giveOrder(const HumanPerception& i_HP)
{
    unsigned int attempts(0);
    Direction dir(i_HP.getPosition().facingDir());
    while ((!i_HP.isWithinMapLimits(dir) ||
        !i_HP.getTileInDir(dir).isPassable()) && attempts < 100) {
        dir = randDirNoCenter();
        ++attempts;
    }
    return Order(WALK, dir);
}