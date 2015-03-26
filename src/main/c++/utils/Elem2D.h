#pragma once
#include <assert.h>
#include "Direction.h"

#define Coord       Elem2D<unsigned int>
#define DCoord      Elem2D<double>
#define Dimensions  Elem2D<unsigned int>

template <typename T>
struct Elem2D
{
    T x;
    T y;

    // CONSTRUCTOR/DESTRUCTOR
    Elem2D<T>() {}
    Elem2D<T>(T i_X, T i_Y): x(i_X), y(i_Y) {}
    Elem2D<T>(const Elem2D<T>& i_Other): x(i_Other.x), y(i_Other.y) {}

    // OPERATORS
    Elem2D<T>& operator+=(const Elem2D<T>& i_Other)
    {
        x += i_Other.x;
        y += i_Other.y;
        return *this;
    }
    Elem2D<T>& operator-=(const Elem2D<T>& i_Other)
    {
        x -= i_Other.x;
        y -= i_Other.y;
        return *this;
    }
    Elem2D<T>& operator*=(const Elem2D<T>& i_Other)
    {
        x *= i_Other.x;
        y *= i_Other.y;
        return *this;
    }
    Elem2D<T>& operator/=(const Elem2D<T>& i_Other)
    {
        x /= i_Other.x;
        y /= i_Other.y;
        return *this;
    }
    
    Elem2D<T>& operator+=(T i_Factor)
    {
        x += i_Factor;
        y += i_Factor;
        return *this;
    }
    Elem2D<T>& operator-=(T i_Factor)
    {
        x -= i_Factor;
        y -= i_Factor;
        return *this;
    }
    Elem2D<T>& operator*=(T i_Factor)
    {
        x *= i_Factor;
        y *= i_Factor;
        return *this;
    }
    Elem2D<T>& operator/=(T i_Factor)
    {
        x /= i_Factor;
        y /= i_Factor;
        return *this;
    }

    // INCREMENT
    Elem2D<T>& incrementInDirection(Direction i_Dir)
    {
        assert(i_Dir != MIDDLE);

        switch (i_Dir) {
        case LEFT:			x -= 1;			break;
        case RIGHT:			x += 1;	        break;
        case UP:					y -= 1;	break;
        case DOWN:					y += 1;	break;
        case UPPER_LEFT:	x -= 1; y -= 1; break;
        case UPPER_RIGHT:	x += 1; y -= 1; break;
        case LOWER_LEFT:	x -= 1; y += 1; break;
        case LOWER_RIGHT:	x += 1; y += 1; break;
        }

        return *this;
    }
};

static unsigned int area(Dimensions i_Dim)
{
    return i_Dim.x * i_Dim.y;
}

template <typename T>
Elem2D<T> operator+(const Elem2D<T>& i_Elem, T i_Factor)
{
    return Elem2D<T>(i_Elem) += i_Factor;
}

template <typename T>
Elem2D<T> operator-(const Elem2D<T>& i_Elem, T i_Factor)
{
    return Elem2D<T>(i_Elem) -= i_Factor;
}

template <typename T>
Elem2D<T> operator*(const Elem2D<T>& i_Elem, T i_Factor)
{
    return Elem2D<T>(i_Elem) *= i_Factor;
}

template <typename T>
Elem2D<T> operator/(const Elem2D<T>& i_Elem, T i_Factor)
{
    return Elem2D<T>(i_Elem) /= i_Factor;
}

template <typename T>
Elem2D<T> operator+(const Elem2D<T>& i_ElemA, const Elem2D<T>& i_ElemB)
{
    return Elem2D<T>(i_ElemA) += i_ElemB;
}

template <typename T>
Elem2D<T> operator-(const Elem2D<T>& i_ElemA, const Elem2D<T>& i_ElemB)
{
    return Elem2D<T>(i_ElemA) -= i_ElemB;
}

template <typename T>
Elem2D<T> operator*(const Elem2D<T>& i_ElemA, const Elem2D<T>& i_ElemB)
{
    return Elem2D<T>(i_ElemA) *= i_ElemB;
}

template <typename T>
Elem2D<T> operator/(const Elem2D<T>& i_ElemA, const Elem2D<T>& i_ElemB)
{
    return Elem2D<T>(i_ElemA) /= i_ElemB;
}

template <typename T>
bool operator==(const Elem2D<T>& i_ElemA, const Elem2D<T>& i_ElemB)
{
    return i_ElemA.x == i_ElemB.x && i_ElemA.y == i_ElemB.y;
}

template <typename T>
Elem2D<T> incrementedToDirection(const Elem2D<T>& i_Elem, Direction i_Dir)
{
    return Elem2D<T>(i_Elem).incrementInDirection(i_Dir);
}