#pragma once
#include <assert.h>
#include "Human.h"

class Civilization
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	Civilization();
    ~Civilization();

	// GETTERS
	Human& getHuman(UINT i_ID) const;
	  
	// STATUS
	UINT getPopulation() const;

protected:
    UINT    m_Pop;
	Human** m_People;
};