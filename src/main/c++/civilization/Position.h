#pragma once
#include "..\Parameters.h"

struct Position
{
	Coord<float> m_Coord;
	Direction    m_FacingDir;

	// CONSTRUCTOR/DESTRUCTOR
	Position(Coord<float> i_Coord, Direction i_FacingDir);
	Position(Direction i_FacingDir, Coord<int> i_Coord);

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
