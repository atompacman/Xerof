#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\..\utils\Elem2D.h"
#include "HumanProcess.h"
#include "..\..\Parameters.h"
#include "..\..\civ\human\Position.h"
/*============================================================================||
| A movement than occurs over many frames
|-----------------------------------------------------------------------------||
| Title says it all
\=============================================================================*/

class MoveProcess : public HumanProcess
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    MoveProcess(Human* i_Human, const Position& i_Dest);

	// NEXT ITERATION
    virtual void nextIter();

private:
    static const double s_ERROR;

	DCoord m_Delta;
};