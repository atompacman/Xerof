#pragma once
#include "Civilization.h"
#include "..\utils\Direction.h"
#include "..\utils\Elem2D.h"

class CivController: public Civilization
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	CivController();

	// DAWN OF CIVILIZATION
	void placeFirstHuman();

	// ADD
	void addHuman(Coord i_Pos);

	// GETTERS
	Human* getHuman(UINT i_ID);
};