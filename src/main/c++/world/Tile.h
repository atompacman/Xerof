#pragma once
#include "Environnement.h"
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
	void setEnvironnement(EnvType);

	// REMOVE
	void removeObject(Direction);

	// GETTERS
	Object* getObject(Direction) const;
	Environnement* getEnvironnement() const;

	// HAS
	bool hasObject(Direction) const;
	bool hasObject() const;
	bool hasEnvironnement() const;

	// STATUS
	bool isPassable() const;

private:
	Object** objects;
	Environnement* environnement;
};