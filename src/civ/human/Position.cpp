#include <Position.h>
#include <Random.h>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Position::Position(Coord i_Coord) :
Position(DCoord((double) i_Coord.x + 0.5, 
                (double) i_Coord.y + 0.5), randDirNoCenter())
{}

Position::Position(DCoord i_Coord) :
Position(i_Coord, randDirNoCenter())
{}

Position::Position(Coord i_Coord, Direction i_FacingDir) :
Position(DCoord((double) i_Coord.x + 0.5,
                (double) i_Coord.y + 0.5), i_FacingDir)
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

DCoord Position::coord() const
{
    return m_Coord;
}

Direction Position::facingDir() const
{
    return m_Dir;
}

Coord Position::tileCoord() const
{
    return Coord((unsigned int)m_Coord.x, (unsigned int)m_Coord.y);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   SETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Position::setCoord(DCoord i_Coord)
{
    m_Coord = i_Coord;
}

void Position::moveForward(DCoord i_Delta)
{
    m_Coord += i_Delta;
}

void Position::setDir(Direction i_Dir)
{
    m_Dir = i_Dir;
}

void Position::setX(double i_X)
{
    m_Coord.x = i_X;
}

void Position::setY(double i_Y)
{
    m_Coord.y = i_Y;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                 OPERATORS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Position::operator==(const Position& i_Other) const
{
    return m_Coord == i_Other.m_Coord;
}