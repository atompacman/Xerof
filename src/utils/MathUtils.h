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

// Really fast conversion to replace rint()
inline int fastRint(double d)
{
    union Cast
    {
        double d;
        long l;
    };
    volatile Cast c;
    c.d = d + 6755399441055744.0;
    return c.l;
}