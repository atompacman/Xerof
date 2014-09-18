#pragma once
#include "..\civilization\Civilization.h"
#include "Order.h"

class AI
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	AI(Civilization*);

	// MOVE HUMAN
	virtual Order giveOrder(Human& human) = 0;

protected:
	Civilization* civ;
};