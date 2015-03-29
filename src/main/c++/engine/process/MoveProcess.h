#pragma once
#include "HumanProcess.h"

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