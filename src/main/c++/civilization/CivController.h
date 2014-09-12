#pragma once
#include "Civilization.h"

class CivController: public Civilization
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	CivController();

	// DAWN OF CIVILIZATION
	void placeFirstHuman();

	// ADD
	void addHuman(Coord<int>);

	// GETTERS
	Human* getHumanPtr(unsigned int id);
};