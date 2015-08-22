#pragma once

#include <Elem2D.h>
#include <Process.h>

/*============================================================================\\
| A movement than occurs over many frames
|-----------------------------------------------------------------------------||
| Title says it all
\=============================================================================*/

class  Individual;
struct Position;
class  Map;

class MoveProcess : public Process
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    MoveProcess(Individual& i_Indiv, const Position& i_Dest, Map& i_Map);

    // NEXT ITERATION
    virtual void nextIter();

private:
    static const double s_DELTA;

    Individual& m_Individual;
    Coord       m_InitTile;
    Coord       m_DestTile;
    DCoord      m_Delta;
    Map&        m_Map;
};