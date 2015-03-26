#pragma once
#include "..\utils\Direction.h"
#include "..\utils\Elem2D.h"
#include "..\Parameters.h"

struct Position
{
	DCoord    m_Coord;
	Direction m_FacingDir;

	// CONSTRUCTOR/DESTRUCTOR
	Position(DCoord i_Coord, Direction i_FacingDir);
    Position(Coord i_Coord, Direction i_FacingDir);

	// OPERATORS
	bool operator==(Position i_Other);
};

static bool isFourWayDirection(Direction i_Dir)
{
    return i_Dir < 4;
}

static bool isDiagonalDirection(Direction i_Dir)
{
    return i_Dir >= 4 && i_Dir < 8;
}
