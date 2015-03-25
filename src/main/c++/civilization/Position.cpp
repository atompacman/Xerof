#include "Position.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Position::Position(Coord<float> i_Coord, Direction i_FacingDir)
{
	assert(i_FacingDir != MIDDLE);
	this->m_Coord = i_Coord;
	this->m_FacingDir = i_FacingDir;
}

Position::Position(Direction i_FacingDir, Coord<int> i_Coord)
{
	assert(i_FacingDir != MIDDLE);
	this->m_Coord = Coord<float>(i_Coord.x, i_Coord.y);
	this->m_FacingDir = i_FacingDir;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                 OPERATORS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Position::operator==(Position i_Other)
{
	return m_Coord.x == i_Other.m_Coord.x && m_Coord.y == i_Other.m_Coord.y;
}