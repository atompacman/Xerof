#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\..\civ\human\HumanInfo.h"
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
    HumanProcess(HumanInfo& i_Human) :
        m_Human(i_Human)
    {}

	// NEXT ITERATION
	virtual void nextIter() = 0;

protected:
    HumanInfo& m_Human;
};