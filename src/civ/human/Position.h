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
	// CONSTRUCTOR/DESTRUCTOR
    Position(Coord  i_Coord);
    Position(DCoord i_Coord);
    Position(Coord  i_Coord, Direction i_FacingDir);
	Position(DCoord i_Coord, Direction i_FacingDir);

    // GETTERS
    DCoord    coord() const;
    Direction facingDir() const;
    Coord     tileCoord() const;

    // SETTERS
    void setCoord(DCoord i_Coord);
    void incremCoord(DCoord i_Delta);
    void setDir(Direction i_Dir);

	// OPERATORS
	bool operator==(const Position& i_Other) const;

private:
    DCoord    m_Coord;
    Direction m_Dir;
};