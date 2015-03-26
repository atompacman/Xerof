#pragma once
#include <assert.h>
#include <ctime>
#include <stdlib.h>
#include "..\Parameters.h"

static void initWorldGeneratorSeed()
{
	if (RANDOM_SEED) {
		srand((unsigned int)time(NULL));
	}
	else {
		srand(WORLD_GENERATION_SEED);
	}
}

static int nextRand(int i_Min, int i_Max)
{
	assert(i_Min <= i_Max && i_Max > 0);
	return rand() % (i_Max - i_Min + 1) + i_Min;
}

static int nextRand(int i_Max)
{
	return nextRand(0, i_Max);
}