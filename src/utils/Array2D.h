#pragma once

#include <Elem2D.h>
#include <vector>

/*============================================================================||
| Data structure representing a fixed 2D array
|-----------------------------------------------------------------------------||
| - Adds constructors and access operators to a std::vector
\=============================================================================*/

template <typename T>
class Array2D : private std::vector<T>
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Array2D<T>(Dimensions i_Dim) :
        std::vector<T>(i_Dim.x * i_Dim.y),
        m_Dim(i_Dim)
    {}
    Array2D<T>(unsigned int i_Width, unsigned int i_Height) :
        this(i_Width * i_Height)
        m_Dim(i_Width, i_Height)
    {}

    // ACCESS OPERATORS
    T& operator()(Coord i_Coord)
    {
        assert(i_Coord < m_Dim);
        return operator[](i_Coord.x + i_Coord.y * m_Dim.x);
    }
    const T& operator()(Coord i_Coord) const
    {
        assert(i_Coord < m_Dim);
        return operator[](i_Coord.x + i_Coord.y * m_Dim.x);
    }
    T& operator()(unsigned int i_X, unsigned int i_Y)
    {
        assert(i_X < m_Dim.x && i_Y < m_Dim.y);
        return operator[](i_X + i_Y * m_Dim.x);
    }
    const T& operator()(unsigned int i_X, unsigned int i_Y) const
    { 
        assert(i_X < m_Dim.x && i_Y < m_Dim.y);
        return operator[](i_X + i_Y * m_Dim.x);
    }

    // STATUS
    unsigned int width()      const { return m_Dim.x; }
    unsigned int height()     const { return m_Dim.y; }
    Dimensions   dimensions() const { return m_Dim; }
    unsigned int area()       const { return m_Dim.x * m_Dim.y; }

protected:
    Dimensions m_Dim;
};
