#pragma once
#include "allegro5\allegro.h"
#include "..\ai\AtomAI.h"
#include "Display.h"
#include "Keyboard.h"
#include "MoveProcess.h"

class GameLoop
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	GameLoop(Display*, Mouse*, Keyboard*);
	~GameLoop();

	// START
	bool start();

private:
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* screenRefresher;

	CivController** civilizations;
	AI** ais;
	
	int nbMoveProcess;
	MoveProcess** moveProcesses;

	Display* display;
	Mouse* mouse;
	Keyboard* keyboard;
	ALLEGRO_BITMAP** assets;

	// CONSTRUCTOR/DESCTRUCTOR
	void initializeCivsAndAIs();

	// UPDATE
	bool updateGame();
	bool processAI();
	bool processOrder(Human*, const Order&);
	bool processMovingOrder(Human*, PossibleOrders, Direction);
	bool verifyDestination(const Position&) const;
	bool isOccupied(Coord<int>) const;

	// UPDATE ANIMATIONS
	void updateMovements();

	// END
	void endProcesses();

	// OTHER
	void printError(const char* msg);
};