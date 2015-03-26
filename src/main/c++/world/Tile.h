#pragma once
#include <assert.h>
#include "Environment.h"
#include "Object.h"

class Tile
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	Tile();
	~Tile();

	// SETTERS
    void setObject(Direction i_Dir, Object* i_Obj);
    void setEnvironment(EnvType i_Type);

	// REMOVE
    void removeObject(Direction i_Dir);

	// GETTERS
    Object* getObject(Direction i_Dir) const;
	Environment* getEnvironment() const;

	// HAS
    bool hasObject(Direction i_Dir) const;
	bool hasObject() const;
	bool hasEnvironment() const;

	// STATUS
	bool isPassable() const;

private:
	Object**     m_Objs;
	Environment* m_Env;
};