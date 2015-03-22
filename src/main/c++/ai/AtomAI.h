#pragma once
#include "AI.h"

class AtomAI: public AI
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	AtomAI(Civilization* i_Civ);

	// GIVE ORDER
	Order giveOrder(Human& i_Human);

private:
	// HELPERS
	void printSurroundingTiles(const Human& i_Human);
};