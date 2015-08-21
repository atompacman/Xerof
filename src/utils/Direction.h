#pragma once

#include <assert.h>
#include <map>
#include <Random.h>

/*============================================================================//
| Different types of direction
|-----------------------------------------------------------------------------||
| - Basic (up, down, left, right)
| - Diagonal (4 corners)
| - The "special" center value
|
| A Direction is basically a unsigned int that must be asserted before usage
\=============================================================================*/

typedef unsigned int Direction;

enum BasicDir
{
    UP          = 0,
    RIGHT       = 1, 
    DOWN        = 2,
    LEFT        = 3
};

enum DiagonalDir
{
    UPPER_RIGHT = 4,
    LOWER_RIGHT = 5,
    LOWER_LEFT  = 6,
    UPPER_LEFT  = 7,
};

#define CENTER 8

static const std::map<std::string, BasicDir> CARDINAL_DIRS = {
    { "NORTH",  UP    },
    { "EAST",   RIGHT },
    { "SOUTH",  DOWN  },
    { "WEST",   LEFT  }
};

static bool isBasicDir(Direction i_Dir)
{
    return i_Dir <= LEFT;
}

static bool isDiagonal(Direction i_Dir)
{
    return UPPER_RIGHT <= i_Dir && i_Dir <= UPPER_LEFT;
}

static bool isNonCenterDir(Direction i_Dir)
{
    return i_Dir < CENTER;
}

static bool isDirection(Direction i_Dir)
{
    return i_Dir <= CENTER;
}

static void assertBasicDir(Direction i_Dir)
{
    assert(isBasicDir(i_Dir));
}

static void assertDiagDir(Direction i_Dir)
{
    assert(isDiagonal(i_Dir));
}

static void assertNonCenterDir(Direction i_Dir)
{
    assert(isNonCenterDir(i_Dir));
}

static void assertDir(Direction i_Dir)
{
    assert(isDirection(i_Dir));
}

static BasicDir randBasicDir()
{
    return BasicDir(randUINT(LEFT));
}

static DiagonalDir randDiagDir()
{
    return DiagonalDir(randUINT(UPPER_RIGHT, UPPER_LEFT));
}

static Direction randDirNoCenter()
{
    return randUINT(UPPER_LEFT);
}

struct Disposition
{
    BasicDir m_BasicDir;
    bool     m_Flip;

    Disposition(BasicDir i_BasicDir, bool i_Flip) :
        m_BasicDir(i_BasicDir),
        m_Flip(i_Flip)
    {}

    Disposition(BasicDir i_BasicDir) :
        m_BasicDir(i_BasicDir),
        m_Flip(randBool())
    {}

    Disposition() :
        m_BasicDir(randBasicDir()),
        m_Flip(randBool())
    {}
};
