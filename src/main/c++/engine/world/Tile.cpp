#include "Tile.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Tile::Tile()
{
	front = nullptr;
	back = nullptr;
}

Tile::~Tile()
{

}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   SETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

void Tile::setForeground(Foreground* front)
{
	this->front = front;
}

void Tile::setBackground(Background* back)
{
	this->back = back;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   GETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

const Foreground* Tile::getForeground() const
{
	return front;
}

const Background* Tile::getBackground() const
{
	return back;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   STATUS                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

bool Tile::hasForeground() const
{
	return front != nullptr;
}

bool Tile::hasBackground() const
{
	return back != nullptr;
}

bool Tile::isPassable() const
{
	return front->isPassable() && back->isPassable();
}