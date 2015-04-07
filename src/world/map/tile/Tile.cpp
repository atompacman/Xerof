#include "Tile.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Tile::Tile() :
m_Env(OCEAN),
m_Objs(new Object*[4]),
m_Human(NULL)
{}

Tile::~Tile()
{
    for (UINT i = 0; i < 4; ++i) {
        //delete[] m_Objs[i];
    }
	//delete[] m_Objs;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   SETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Tile::setObject(Direction i_Dir, Object* i_Obj)
{
    assertDiagDir(i_Dir);
	assert(!hasObject(i_Dir));
	m_Objs[i_Dir - UPPER_LEFT] = i_Obj;
}

void Tile::setEnvironment(EnvType i_Type)
{
    m_Env.setEnvType(i_Type);
}

void Tile::setHuman(HumanInfo* i_Human)
{
    m_Human = i_Human;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    REMOVE                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Tile::removeObject(Direction i_Dir)
{
    assertDiagDir(i_Dir);
    delete m_Objs[i_Dir - UPPER_RIGHT];
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Environment& Tile::getEnvironment() const
{
	return m_Env;
}

Object* Tile::getObject(Direction i_Dir) const
{
    assert(hasObject(i_Dir));
    return m_Objs[i_Dir - UPPER_RIGHT];
}

const HumanInfo* Tile::getHuman() const
{
    return m_Human;
}

HumanInfo* Tile::getHuman()
{
    return m_Human;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     HAS                                    //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Tile::hasObject(Direction i_Dir) const
{
    assertDiagDir(i_Dir);
    return m_Objs[i_Dir - UPPER_RIGHT] != NULL;
}

bool Tile::hasObject() const
{
	return hasObject(UPPER_LEFT) || hasObject(UPPER_RIGHT) || 
		   hasObject(LOWER_LEFT) || hasObject(LOWER_RIGHT);
}

bool Tile::hasHuman() const
{
    return m_Human != NULL;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    STATUS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Tile::isPassable() const
{
	return m_Env.isSolidLand();
}