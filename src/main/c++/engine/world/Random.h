#pragma once
#include <assert.h>
#include <stdlib.h>

const static unsigned int WORLD_GENERATION_SEED = 47474;

static void initWorldGeneratorSeed()
{
	srand(WORLD_GENERATION_SEED);
}

static unsigned int nextRand(int min, int max)
{
	assert(min <= max && max > 0);
	return rand() % (max - min + 1) + min;
}

static unsigned int nextRand(int max)
{
	return nextRand(0, max);
}