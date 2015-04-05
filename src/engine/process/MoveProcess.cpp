#include "MoveProcess.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const double MoveProcess::s_ERROR = 1.0 / (TARGET_FPS * 2.0);

MoveProcess::MoveProcess(HumanInfo& i_Human, const Position& i_Dest) :
HumanProcess(i_Human),
m_Delta((i_Dest.m_Coord - m_Human.getPos().m_Coord) / TARGET_FPS)
{
    m_Human.getPos().setDir(i_Dest.m_Dir);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                               NEXT ITERATION                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void MoveProcess::nextIter()
{
    // Increment position in facing direction
    Position& pos(m_Human.getPos());
    pos.incremCoord(m_Delta);

    // If the position is really close to be right on a tile intersection,
    // set position to be on this intersection
    DCoord corrected(pos.m_Coord);
    double x = pos.m_Coord.x;
    double y = pos.m_Coord.y;

    if (abs(x - rint(x)) < s_ERROR) {
        corrected.x = rint(x);
	}
    if (abs(y - rint(y)) < s_ERROR) {
        corrected.y = rint(y);
	}
    pos.setCoord(corrected);
}