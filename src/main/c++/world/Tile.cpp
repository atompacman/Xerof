#include "Tile.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Tile::Tile():
m_Objs(new Object*[4]),
m_Env(OCEAN)
{}

Tile::~Tile()
{
    for (int i = 0; i < 4; ++i) {
        delete[] m_Objs[i];
    }
	delete[] m_Objs;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   SETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Tile::setObject(Direction i_Dir, Object* i_Obj)
{
	assert(isDiagonalDirection(i_Dir));
	assert(!hasObject(i_Dir));
	m_Objs[i_Dir - UPPER_LEFT] = i_Obj;
}

void Tile::setEnvironment(EnvType i_Type)
{
    m_Env = Environment(i_Type);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    REMOVE                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Tile::removeObject(Direction i_Dir)
{
	assert(isDiagonalDirection(i_Dir));
	delete m_Objs[i_Dir - UPPER_LEFT];
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Object* Tile::getObject(Direction i_Dir) const
{
	assert(hasObject(i_Dir));
	return m_Objs[i_Dir - UPPER_LEFT];
}

const Environment& Tile::getEnvironment() const
{
	return m_Env;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     HAS                                    //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Tile::hasObject(Direction i_Dir) const
{
	assert(isDiagonalDirection(i_Dir));
	return m_Objs[i_Dir - UPPER_LEFT] != nullptr;
}

bool Tile::hasObject() const
{
	return hasObject(UPPER_LEFT) || hasObject(UPPER_RIGHT) || 
		hasObject(LOWER_LEFT) || hasObject(LOWER_RIGHT);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    STATUS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Tile::isPassable() const
{
	return m_Env.isSolidLand();
}