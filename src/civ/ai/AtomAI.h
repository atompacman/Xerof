#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <iomanip>
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include <easylogging++.h>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "AI.h"
#include "..\..\utils\Random.h"
#include "..\..\world\map\tile\Tile.h"
/*============================================================================||
| AI made by Atompacman
|-----------------------------------------------------------------------------||
| Implements the AI abstract class
\=============================================================================*/

class AtomAI : public AI
{
public:
	// GIVE ORDER
    virtual Order giveOrder(const Human& i_Human);

private:
	// HELPERS
	void printSurroundingTiles(const Human& i_Human);
};