#pragma once
#include "..\Parameters.h"
#include <assert.h>
#include <ctime>
#include <stdlib.h>

static void initWorldGeneratorSeed()
{
	if (RANDOM_SEED) {
		srand((unsigned int)time(NULL));
	}
	else {
		srand(WORLD_GENERATION_SEED);
	}
}

static int nextRand(int min, int max)
{
	assert(min <= max && max > 0);
	return rand() % (max - min + 1) + min;
}

static int nextRand(int max)
{
	return nextRand(0, max);
}