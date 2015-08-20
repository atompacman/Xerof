#pragma once

#include <AI.h>

/*============================================================================\\
| AI made by Atompacman
|-----------------------------------------------------------------------------||
| Implements the AI abstract class
\=============================================================================*/

class AtomAI : public AI
{
public:
    // GIVE ORDER
    virtual Order giveOrder(const HumanPerception& i_HP);
};