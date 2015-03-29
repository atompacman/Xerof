#pragma once
#include "..\civilization\Civilization.h"
#include "..\utils\Direction.h"
#include "Order.h"

class AI
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	AI(const Civilization& i_Civ);

	// MOVE HUMAN
	virtual Order giveOrder(const Human& i_Human) = 0;

protected:
	const Civilization& m_Civ;
};