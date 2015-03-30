#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <assert.h>
#include <ctime>
#include <stdlib.h>
#include <wtypes.h>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Direction.h"
#include "..\Parameters.h"
/*============================================================================||
| Random number manager
|-----------------------------------------------------------------------------||
| - UINT
| - Probability [0-1]
| - Directions
\=============================================================================*/

static void initRandSeed()
{
	if (RANDOM_SEED) {
		srand((UINT)time(NULL));
	}
	else {
		srand(WORLD_GENERATION_SEED);
	}
}

static UINT randUINT(UINT i_Min, UINT i_Max)
{
	assert(i_Min <= i_Max);
	return rand() % (i_Max - i_Min + 1) + i_Min;
}

static UINT randUINT(UINT i_Max)
{
	return randUINT(0, i_Max);
}

static double randProb()
{
    return (double)rand() / (RAND_MAX);
}

static Direction randBasicDir()
{
    return randUINT(LEFT);
}

static Direction randDirNoCenter()
{
    return randUINT(UPPER_LEFT);
}