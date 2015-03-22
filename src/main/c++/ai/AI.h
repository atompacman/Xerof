#pragma once
#include "..\civilization\Civilization.h"
#include "Order.h"

class AI
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	AI(Civilization* i_Civ);

	// MOVE HUMAN
	virtual Order giveOrder(const Human& i_Human) = 0;

protected:
	Civilization* m_Civ;
};