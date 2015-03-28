#pragma once
#include <math.h>

#define EPSILON 1e-9;

bool almostEqual(double a, double b)
{
    return fabs(a - b) < EPSILON;
}