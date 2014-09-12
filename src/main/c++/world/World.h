#pragma once
#include "Map.h"
#include <assert.h>

class World
{
public:
	Map* map;

	// GET INSTANCE
	const static World* getInstance() 
	{
		if (world == nullptr) { world = new World(); }
		return world;
	}

private:
	static World* world;

	// CONSTRUCTOR/DESCTRUCTOR
	World();
};
