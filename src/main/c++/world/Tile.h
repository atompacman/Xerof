#pragma once
#include "Environment.h"
#include "Object.h"
#include <assert.h>

class Tile
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	Tile();
	~Tile();

	// SETTERS
	void setObject(Direction, Object*);
	void setEnvironment(EnvType);

	// REMOVE
	void removeObject(Direction);

	// GETTERS
	Object* getObject(Direction) const;
	Environment* getEnvironment() const;

	// HAS
	bool hasObject(Direction) const;
	bool hasObject() const;
	bool hasEnvironment() const;

	// STATUS
	bool isPassable() const;

private:
	Object** objects;
	Environment* environment;
};