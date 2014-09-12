#pragma once
#include "Human.h"
#include <assert.h>

class Civilization
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	Civilization();

	// GETTERS
	Human& getHuman(unsigned int id) const;
	  
	// STATUS
	unsigned int getPopulation() const;

protected:
	unsigned int population;
	Human** people;
};