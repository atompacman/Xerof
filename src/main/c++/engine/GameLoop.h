#pragma once
#include "allegro5\allegro.h"
#include "..\ai\AtomAI.h"
#include "Display.h"
#include "Keyboard.h"
#include "MoveProcess.h"

class GameLoop
{
public:
	// START
	static void run();

private:
    Mouse                m_Mouse;
    Keyboard             m_Keyboard;
    Display              m_Disp;

	ALLEGRO_EVENT_QUEUE* m_Queue;
	ALLEGRO_TIMER*       m_ScreenRefresher;

	CivController**      m_CivCtrlrs;
	AI**                 m_AIs;
	
	UINT                 m_NumMoveProcs;
	MoveProcess**        m_MoveProcs;

    // CONSTRUCTOR/DESTRUCTOR
    GameLoop();
    void initializeCivsAndAIs();
    ~GameLoop();

    // START
    void startGame();

	// UPDATE
	void updateGame();
	bool processAI();
    bool processOrder(Human* io_Human, const Order& i_Order);
    bool processMovingOrder(Human*         i_Human,
                            PossibleOrders i_Action,
                            Direction      i_Dir);
    bool verifyDestination(const Position& i_Dest) const;
    bool isOccupied(Coord i_Coord) const;
	void updateMovements();

	// END
	void endProcesses();
};