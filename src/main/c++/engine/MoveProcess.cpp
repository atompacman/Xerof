#include "MoveProcess.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

MoveProcess::MoveProcess(Human* human, const Position& destination)
{
	human->m_Pos.m_FacingDir = destination.m_FacingDir;
	delta.x = (destination.m_Coord.x - human->m_Pos.m_Coord.x) / TARGET_FPS;
	delta.y = (destination.m_Coord.y - human->m_Pos.m_Coord.y) / TARGET_FPS;
	this->human = human;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//               NEXT ITERATION                //
//- - - - - - - - - - - - - - - - - - - - - - -//

void MoveProcess::nextIteration()
{
	human->m_Pos.m_Coord += delta;

	float x = human->m_Pos.m_Coord.x;
	float y = human->m_Pos.m_Coord.y;

	float error = 1.0 / (TARGET_FPS * 2.0);

	if (abs(x - rint(x)) < error) {
		human->m_Pos.m_Coord.x = rint(x);
	}
	if (abs(y - rint(y)) < error) {
		human->m_Pos.m_Coord.y = rint(y);
	}
}