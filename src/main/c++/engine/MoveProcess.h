#pragma once
#include "..\civilization\Human.h"

class MoveProcess
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    MoveProcess(Human* i_Human, const Position& i_Dest);

	// NEXT ITERATION
	void nextIteration();

private:
	Human*       m_Human;
	Coord<float> m_Delta;
};