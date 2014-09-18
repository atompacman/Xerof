#pragma once
#include "AI.h"

class AtomAI: public AI
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	AtomAI(Civilization*);

	// MOVE HUMAN
	Order giveOrder(Human& human);

private:
	// HELPERS
	void printSurroundingTiles(const Human& human);
};