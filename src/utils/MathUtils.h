#pragma once

#include <math.h>

/*============================================================================\\
| Math shortcuts and definitions
|-----------------------------------------------------------------------------||
| - Double (almost) equal
\=============================================================================*/

#define EPSILON 1e-12

static bool almostEqual(double a, double b)
{
    return fabs(a - b) < EPSILON;
}