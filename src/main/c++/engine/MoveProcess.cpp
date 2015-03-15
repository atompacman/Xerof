#include "MoveProcess.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

MoveProcess::MoveProcess(Human* human, const Position& destination)
{
	human->position.facingDirection = destination.facingDirection;
	delta.x = (destination.coord.x - human->position.coord.x) / TARGET_FPS;
	delta.y = (destination.coord.y - human->position.coord.y) / TARGET_FPS;
	this->human = human;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//               NEXT ITERATION                //
//- - - - - - - - - - - - - - - - - - - - - - -//

void MoveProcess::nextIteration()
{
	human->position.coord += delta;

	float x = human->position.coord.x;
	float y = human->position.coord.y;

	float error = 1.0 / (TARGET_FPS * 2.0);

	if (abs(x - rint(x)) < error) {
		human->position.coord.x = rint(x);
	}
	if (abs(y - rint(y)) < error) {
		human->position.coord.y = rint(y);
	}
}