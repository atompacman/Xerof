#include "Position.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Position::Position(DCoord i_Coord, Direction i_FacingDir):
m_Coord(i_Coord),
m_FacingDir(i_FacingDir)
{
	assert(i_FacingDir != MIDDLE);
}

Position::Position(Coord i_Coord, Direction i_FacingDir):
Position(DCoord(i_Coord.x, i_Coord.y), i_FacingDir)
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                 OPERATORS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Position::operator==(Position i_Other)
{
    return m_Coord == i_Other.m_Coord;
}