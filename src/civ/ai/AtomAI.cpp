#include <AtomAI.h>
#include <Direction.h>
#include <HumanPerception.h>
#include <Order.h>
#include <Position.h>
#include <Random.h>
#include <Tile.h>

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