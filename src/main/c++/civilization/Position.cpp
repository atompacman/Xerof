#include "Position.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Position::Position(Coord<float> coord, Direction facingDirection)
{
	assert(facingDirection != MIDDLE);
	this->coord = coord;
	this->facingDirection = facingDirection;
}

Position::Position(Direction facingDirection, Coord<int> coord)
{
	assert(facingDirection != MIDDLE);
	this->coord = Coord<float>(coord.x, coord.y);
	this->facingDirection = facingDirection;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                  OPERATORS                  //
//- - - - - - - - - - - - - - - - - - - - - - -//

bool Position::operator==(Position other)
{
	return coord.x == other.coord.x && coord.y == other.coord.y;
}