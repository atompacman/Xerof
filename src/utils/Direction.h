#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <assert.h>
/*============================================================================||
| Different types of direction
|-----------------------------------------------------------------------------||
| - Basic (up, down, left, right)
| - Diagonal (4 corners)
| - The "special" center value
|
| A Direction is basically a UINT that must be asserted before usage
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

static void assertBasicDir(Direction i_Dir)
{
    assert(i_Dir <= LEFT);
}

static void assertDiagDir(Direction i_Dir)
{
    assert(UPPER_RIGHT <= i_Dir && i_Dir <= UPPER_LEFT);
}

static void assertNonCenterDir(Direction i_Dir)
{
    assert(i_Dir < CENTER);
}