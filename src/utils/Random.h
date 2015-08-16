#pragma once

#include <assert.h>
#include <ctime>
#include <Direction.h>
#include <stdlib.h>

/*============================================================================\\
| Random number manager
|-----------------------------------------------------------------------------||
| - unsigned int
| - Probability [0-1]
| - Directions
\=============================================================================*/

const bool SEED_IS_RANDOM = true;
const int WORLD_GENERATION_SEED = 432;

static void initRandSeed()
{
    if (SEED_IS_RANDOM) {
        srand((unsigned int)time(NULL));
    }
    else {
        srand(WORLD_GENERATION_SEED);
    }
}

static unsigned int randUINT(unsigned int i_Min, unsigned int i_Max)
{
    assert(i_Min <= i_Max);
    return rand() % (i_Max - i_Min + 1) + i_Min;
}

static unsigned int randUINT(unsigned int i_Max)
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