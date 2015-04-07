#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\..\utils\Random.h"
/*============================================================================||
| Coordinates + Facing direction
|-----------------------------------------------------------------------------||
| Little struct
\=============================================================================*/

struct Position
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