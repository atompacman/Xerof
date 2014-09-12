#pragma once
#include "..\civilization\Human.h"

class MoveProcess
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	MoveProcess(Human*, const Position&);

	// NEXT ITERATION
	void nextIteration();

private:
	Human* human;
	Coord<float> delta;
};