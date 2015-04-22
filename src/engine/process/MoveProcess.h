#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "HumanProcess.h"
#include "..\..\world\map\Map.h"
/*============================================================================||
| A movement than occurs over many frames
|-----------------------------------------------------------------------------||
| Title says it all
\=============================================================================*/

class MoveProcess : public HumanProcess
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    MoveProcess(HumanInfo& i_Human, const Position& i_Dest, Map& i_Map);

	// NEXT ITERATION
    virtual void nextIter();

private:
    static const double s_DELTA;

    Coord  m_InitTile;
    Coord  m_DestTile;
	DCoord m_Delta;
    Map&   m_Map;
};