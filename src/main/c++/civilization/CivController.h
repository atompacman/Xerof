#pragma once
#include "Civilization.h"

class CivController: public Civilization
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	CivController();

	// DAWN OF CIVILIZATION
	void placeFirstHuman();

	// ADD
	void addHuman(Coord<int> i_Pos);

	// GETTERS
	Human* getHuman(UINT i_ID);
};