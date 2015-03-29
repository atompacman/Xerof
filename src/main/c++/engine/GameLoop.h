#pragma once
#include "allegro5\allegro.h"
#include "..\ai\AtomAI.h"
#include "Display.h"
#include "Keyboard.h"
#include "process\MoveProcess.h"

class GameLoop
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    GameLoop();
    ~GameLoop();

	// START
    void startGame();

private:
    World                m_World;
    CivController**      m_CivCtrls;

    Mouse                m_Mouse;
    Keyboard             m_Keyboard;
    Display              m_Disp;

	ALLEGRO_EVENT_QUEUE* m_Queue;
	ALLEGRO_TIMER*       m_ScreenRefresher;
	
	UINT                 m_NumMoveProcs;
	MoveProcess**        m_MoveProcs;

    // CONSTRUCTOR/DESTRUCTOR
    CivController** initCivCtrls();

	// UPDATE
	void updateGame();
	void processAI();
    void processOrder(Human& io_Human, const Order& i_Order);
    void processMovingOrder(Human&         io_Human,
                            PossibleOrders i_Action,
                            Direction      i_Dir);
    bool verifyDestination(const Position& i_Dest) const;
    bool isOccupied(Coord i_Coord) const;
	void updateMovements();

	// END
	void endProcesses();
};