#include "Position.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Position::Position(Coord i_Coord) :
Position(DCoord(i_Coord.x, i_Coord.y), randDirNoCenter())
{}

Position::Position(DCoord i_Coord) :
Position(i_Coord, randDirNoCenter())
{}

Position::Position(Coord i_Coord, Direction i_FacingDir) :
Position(DCoord(i_Coord.x, i_Coord.y), i_FacingDir)
{}

Position::Position(DCoord i_Coord, Direction i_FacingDir):
m_Coord(i_Coord),
m_Dir(i_FacingDir)
{
    assertNonCenterDir(m_Dir);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Coord Position::tileCoord() const
{
    return Coord(m_Coord.x, m_Coord.y);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Position::setCoord(DCoord i_Coord)
{
    m_Coord = i_Coord;
}

void Position::incremCoord(DCoord i_Delta)
{
    m_Coord += i_Delta;
}

void Position::setDir(Direction i_Dir)
{
    m_Dir = i_Dir;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                 OPERATORS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Position::operator==(const Position& i_Other) const
{
    return m_Coord == i_Other.m_Coord;
}