#include "MoveProcess.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

MoveProcess::MoveProcess(Human* human, const Position& destination)
{
	human->m_Pos.facingDirection = destination.facingDirection;
	delta.x = (destination.coord.x - human->m_Pos.coord.x) / TARGET_FPS;
	delta.y = (destination.coord.y - human->m_Pos.coord.y) / TARGET_FPS;
	this->human = human;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//               NEXT ITERATION                //
//- - - - - - - - - - - - - - - - - - - - - - -//

void MoveProcess::nextIteration()
{
	human->m_Pos.coord += delta;

	float x = human->m_Pos.coord.x;
	float y = human->m_Pos.coord.y;

	float error = 1.0 / (TARGET_FPS * 2.0);

	if (abs(x - rint(x)) < error) {
		human->m_Pos.coord.x = rint(x);
	}
	if (abs(y - rint(y)) < error) {
		human->m_Pos.coord.y = rint(y);
	}
}