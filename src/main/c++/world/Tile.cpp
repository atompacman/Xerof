#include "Tile.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Tile::Tile()
{
	objects = new Object*[4];
}

Tile::~Tile()
{
	for (int i = 0; i < 4; ++i) {
		delete objects[i];
	}
	delete objects;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                  SETTERS                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

void Tile::setObject(Direction direction, Object* object)
{
	assert(isDiagonalDirection(direction));
	assert(!hasObject(direction));
	objects[direction - UPPER_LEFT] = object;
}

void Tile::setEnvironment(EnvType type)
{
	this->environment = new Environment(type);
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   REMOVE                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

void Tile::removeObject(Direction direction)
{
	assert(isDiagonalDirection(direction));
	delete objects[direction - UPPER_LEFT];
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   GETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

Object* Tile::getObject(Direction direction) const
{
	assert(hasObject(direction));
	return objects[direction - UPPER_LEFT];
}

Environment* Tile::getEnvironment() const
{
	assert(hasEnvironment());
	return environment;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                    HAS                     //
//- - - - - - - - - - - - - - - - - - - - - - -//

bool Tile::hasObject(Direction direction) const
{
	assert(isDiagonalDirection(direction));
	return objects[direction - UPPER_LEFT] != nullptr;
}

bool Tile::hasObject() const
{
	return hasObject(UPPER_LEFT) || hasObject(UPPER_RIGHT) || 
		hasObject(LOWER_LEFT) || hasObject(LOWER_RIGHT);
}

bool Tile::hasEnvironment() const
{
	return environment != nullptr;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   STATUS                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

bool Tile::isPassable() const
{
	return environment->isSolidLand();
}