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

	Coord<T>() : x(0), y(0) {}
	Coord<T>(const T x, const T y) : x(x), y(y) {}


	//= = = = = = = = = = = = = = = = = = = = = = =//
	//                  OPERATORS                  //
	//- - - - - - - - - - - - - - - - - - - - - - -//

	Coord<T>& operator+=(const Coord<T> other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Coord<T>& operator*=(const T factor)
	{
		x *= factor;
		y *= factor;
		return *this;
	}

	Coord<T> operator*(const T factor) const
	{
		return Coord<T>(x * factor, y * factor);
	}


	//= = = = = = = = = = = = = = = = = = = = = = =//
	//          INCREMENTED TO DIRECTION           //
	//- - - - - - - - - - - - - - - - - - - - - - -//

	Coord<T> incrementedToDirection(Direction direction) const
	{
		assert(direction != MIDDLE);

		Coord<T> incremented = Coord(x, y);

		switch (direction) {
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