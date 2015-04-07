#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\Civilization.h"
#include "Order.h"
/*============================================================================||
| Abstract class setting the framwork for AIs
|-----------------------------------------------------------------------------||
| Currently, the only thing an AI can do is give an Order to a Human. AIs
| only knows what the Human knows.
\=============================================================================*/

class AI
{
public:
	// MOVE HUMAN
	virtual Order giveOrder(const Human& i_Human) = 0;
};