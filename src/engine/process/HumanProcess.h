#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\..\civ\human\Human.h"
#include "Process.h"
/*============================================================================||
| All processes involving a Human
|-----------------------------------------------------------------------------||
| - Human movement
\=============================================================================*/

class HumanProcess : public Process
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    HumanProcess(Human* i_Human) :
        m_Human(*i_Human)
    {}

	// NEXT ITERATION
	virtual void nextIter() = 0;

protected:
    Human& m_Human;
};