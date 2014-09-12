#pragma once
#include "..\Parameters.h"

static bool isFourWayDirection(Direction direction)
{
	return direction < 4;
}

static bool isDiagonalDirection(Direction direction)
{
	return direction >= 4 && direction < 8;
}

struct Position
{
	Coord<float> coord;
	Direction facingDirection;

	// CONSTRUCTOR/DESCTRUCTOR
	Position(Coord<float> coord, Direction facingDirection);
	Position(Direction facingDirection, Coord<int> coord);

	// OPERATORS
	bool operator==(Position);
};