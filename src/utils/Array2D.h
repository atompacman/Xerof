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
    Array2D<T>() :
        std::vector<T>(),
        m_Dim(0,0)
    {}
    Array2D<T>(Dimensions i_Dim) :
        std::vector<T>(i_Dim.x * i_Dim.y),
        m_Dim(i_Dim)
    {}
    Array2D<T>(unsigned int i_Width, unsigned int i_Height) :
        this(i_Width * i_Height)
        m_Dim(i_Width, i_Height)
    {}

    // ACCESS OPERATORS
    typename std::vector<T>::reference operator()(Coord i_Coord)
    {
        assert(i_Coord < m_Dim);
        return operator[](i_Coord.x + i_Coord.y * m_Dim.x);
    }
    typename std::vector<T>::const_reference operator()(Coord i_Coord) const
    {
        assert(i_Coord < m_Dim);
        return operator[](i_Coord.x + i_Coord.y * m_Dim.x);
    }
    typename std::vector<T>::reference operator()(unsigned int i_X, 
                                                  unsigned int i_Y)
    {
        assert(i_X < m_Dim.x && i_Y < m_Dim.y);
        return operator[](i_X + i_Y * m_Dim.x);
    }
    typename std::vector<T>::const_reference operator()(unsigned int i_X,
                                                        unsigned int i_Y) const
    { 
        assert(i_X < m_Dim.x && i_Y < m_Dim.y);
        return operator[](i_X + i_Y * m_Dim.x);
    }

    // CLEAR AND RESIZE
    void clearAndResize(Dimensions i_Dim)
    {
        clear();
        m_Dim = i_Dim;
        std::vector<T>::resize(m_Dim.x * m_Dim.y);
    }
    void clearAndResize(unsigned int i_X, unsigned int i_Y)
    {
        clear();
        m_Dim = Dimensions(i_X, i_Y);
        std::vector<T>::resize(i_X * i_Y);
    }

    // STATUS
    unsigned int width()      const { return m_Dim.x; }
    unsigned int height()     const { return m_Dim.y; }
    unsigned int area()       const { return m_Dim.x * m_Dim.y; }
    Dimensions   dimensions() const { return m_Dim; }

protected:
    Dimensions m_Dim;
};
