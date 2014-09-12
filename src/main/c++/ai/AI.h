#pragma once
#include "..\civilization\Civilization.h"
#include "Order.h"

class AI
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	AI(Civilization*);

	// MOVE HUMAN
	virtual Order giveOrderToHuman(Human& human) = 0;

protected:
	Civilization* civ;
};