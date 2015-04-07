#include "MoveProcess.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const double MoveProcess::s_ERROR = 0.5 / TARGET_FPS;

MoveProcess::MoveProcess(HumanInfo& i_Human,const Position& i_Dest, Map& i_Map):
HumanProcess(i_Human),
m_Dest(i_Dest),
m_Delta((i_Dest.coord() - m_Human.getPos().coord()) / TARGET_FPS),
m_Map(i_Map)
{
    m_Human.getPos().setDir(i_Dest.facingDir());
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                               NEXT ITERATION                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void MoveProcess::nextIter()
{
    // Get current position
    Position& pos(m_Human.getPos());

    // Remove human from current tile
    m_Map.getTile(pos.tileCoord()).setHuman(NULL);

    // Increment position in facing direction
    pos.incremCoord(m_Delta);

    // If position is really close to destination, set position to destination
    if (abs(pos.coord().x - m_Dest.coord().x) < s_ERROR &&
        abs(pos.coord().y - m_Dest.coord().y) < s_ERROR) {
        pos.setCoord(m_Dest.coord());
    }

    // Set human on (possibly) new tile
    m_Map.getTile(pos.tileCoord()).setHuman(&m_Human);
}