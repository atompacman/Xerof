#pragma once
#define Dimensions Coord<int>

enum Direction
{
	UP, RIGHT, DOWN, LEFT,
	UPPER_LEFT, UPPER_RIGHT, LOWER_LEFT, LOWER_RIGHT,
	MIDDLE
};

template <typename T>
struct Coord
{
	T x;
	T y;

	//= = = = = = = = = = = = = = = = = = = = = = =//
	//           CONSTRUCTOR/DESCTRUCTOR           //
	//- - - - - - - - - - - - - - - - - - - - - - -//

	Coord<T>() : 
        x(0), y(0) 
    {}

	Coord<T>(const T m_X, const T m_Y) : 
        x(m_X), y(m_Y) 
    {}


	//= = = = = = = = = = = = = = = = = = = = = = =//
	//                  OPERATORS                  //
	//- - - - - - - - - - - - - - - - - - - - - - -//

	Coord<T>& operator+=(const Coord<T> i_Other)
	{
		x += i_Other.x;
		y += i_Other.y;
		return *this;
	}

	Coord<T>& operator*=(const T i_Factor)
	{
		x *= i_Factor;
		y *= i_Factor;
		return *this;
	}

	Coord<T> operator*(const T i_Factor) const
	{
		return Coord<T>(x * i_Factor, y * i_Factor);
	}


	//= = = = = = = = = = = = = = = = = = = = = = =//
	//          INCREMENTED TO DIRECTION           //
	//- - - - - - - - - - - - - - - - - - - - - - -//

	Coord<T> incrementedToDirection(Direction i_Dir) const
	{
		assert(i_Dir != MIDDLE);

		Coord<T> incremented = Coord(x, y);

		switch (i_Dir) {
		case LEFT:			incremented.x -= 1;						break;
		case RIGHT:			incremented.x += 1;						break;
		case UP:								incremented.y -= 1;	break;
		case DOWN:								incremented.y += 1;	break;
		case UPPER_LEFT:	incremented.x -= 1; incremented.y -= 1; break;
		case UPPER_RIGHT:	incremented.x += 1; incremented.y -= 1; break;
		case LOWER_LEFT:	incremented.x -= 1; incremented.y += 1; break;
		case LOWER_RIGHT:	incremented.x += 1; incremented.y += 1; break;
		}
		return incremented;
	}


	//= = = = = = = = = = = = = = = = = = = = = = =//
	//                     AREA                    //
	//- - - - - - - - - - - - - - - - - - - - - - -//

	T area() const
	{
		T area = x * y;
		assert(area >= 0);
		return area;
	}
};