#include "MoveProcess.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

MoveProcess::MoveProcess(Human* i_Human, const Position& i_Dest):
m_Human(i_Human)
{
	i_Human->m_Pos.m_FacingDir = i_Dest.m_FacingDir;
	m_Delta.x = (i_Dest.m_Coord.x - i_Human->m_Pos.m_Coord.x) / TARGET_FPS;
	m_Delta.y = (i_Dest.m_Coord.y - i_Human->m_Pos.m_Coord.y) / TARGET_FPS;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                               NEXT ITERATION                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void MoveProcess::nextIteration()
{
	m_Human->m_Pos.m_Coord += m_Delta;

	float x = m_Human->m_Pos.m_Coord.x;
	float y = m_Human->m_Pos.m_Coord.y;

	float error = 1.0 / (TARGET_FPS * 2.0);

	if (abs(x - rint(x)) < error) {
		m_Human->m_Pos.m_Coord.x = rint(x);
	}
	if (abs(y - rint(y)) < error) {
		m_Human->m_Pos.m_Coord.y = rint(y);
	}
}