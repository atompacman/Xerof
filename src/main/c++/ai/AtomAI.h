#pragma once
#include "AI.h"

class AtomAI : public AI
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    AtomAI(const Civilization& i_Civ);

	// GIVE ORDER
    virtual Order giveOrder(const Human& i_Human);

private:
	// HELPERS
	void printSurroundingTiles(const Human& i_Human);
};