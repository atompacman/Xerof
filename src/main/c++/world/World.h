#pragma once
#include <assert.h>
#include "Map.h"

class World
{
public:
	Map* m_Map;

	// GET INSTANCE
	const static World* getInstance() 
	{
		if (s_World == NULL) { 
            s_World = new World(); 
        }
		return s_World;
	}

private:
	static World* s_World;

	// CONSTRUCTOR/DESTRUCTOR
	World();
};
