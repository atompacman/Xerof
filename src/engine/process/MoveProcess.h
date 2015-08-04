#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Process.h"
#include "..\..\world\map\Map.h"
#include "..\..\utils\MathUtils.h"
/*============================================================================||
| A movement than occurs over many frames
|-----------------------------------------------------------------------------||
| Title says it all
\=============================================================================*/

class MoveProcess : public Process
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    MoveProcess(HumanInfo& i_Human, const Position& i_Dest, Map& i_Map);

	// NEXT ITERATION
    virtual void nextIter();

private:
    static const double s_DELTA;

	HumanInfo& m_Human;
    Coord	   m_InitTile;
    Coord	   m_DestTile;
	DCoord	   m_Delta;
    Map&	   m_Map;
};