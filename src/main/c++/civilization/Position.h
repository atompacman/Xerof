#pragma once
#include "..\utils\Direction.h"
#include "..\utils\Elem2D.h"
#include "..\Parameters.h"
#include "..\utils\Random.h"

class Position
{
public:
    DCoord    m_Coord;
    Direction m_Dir;

	// CONSTRUCTOR/DESTRUCTOR
    Position(Coord  i_Coord);
    Position(DCoord i_Coord);
    Position(Coord  i_Coord, Direction i_FacingDir);
	Position(DCoord i_Coord, Direction i_FacingDir);

    // GETTERS
    Coord     tileCoord() const;

    // SETTERS
    void setCoord(DCoord i_Coord);
    void incremCoord(DCoord i_Delta);
    void setDir(Direction i_Dir);

	// OPERATORS
	bool operator==(const Position& i_Other) const;
};