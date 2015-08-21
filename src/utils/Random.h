#pragma once

#include <assert.h>
#include <ctime>
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

static bool randBool()
{
    return randUINT(0, 1) == 0;
}

static double randProb()
{
    return (double)rand() / (RAND_MAX);
}
