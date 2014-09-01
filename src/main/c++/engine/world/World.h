#pragma once
#include "Map.h"

class World
{
public:
	Map map;

	//CONSTRUCTOR/DESCTRUCTOR
	World();
	~World(){};

	//GETTERS
	bool isNight() const;

	//SETTERS
	void setDay();
	void setNight();

private:
	bool isNightTime;
};