#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <assert.h>
#include <map>
/*============================================================================||
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

#define CENTER 9

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