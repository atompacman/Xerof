#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "AI.h"
#include "..\..\utils\Random.h"
#include "..\..\world\map\tile\Tile.h"
/*============================================================================||
| AI made by Atompacman
|-----------------------------------------------------------------------------||
| Implements the AI abstract class
\=============================================================================*/

class FeroxAI : public AI
{
public:
    // GIVE ORDER
    virtual Order giveOrder(const HumanPerception& i_HP);
};