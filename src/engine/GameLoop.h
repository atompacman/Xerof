#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include "allegro5\allegro.h"
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Display.h"
#include "Keyboard.h"
#include "process\MoveProcess.h"
#include "..\civ\ai\Order.h"
/*============================================================================||
| The main class of the game
|-----------------------------------------------------------------------------||
| Handle the event queue. Manages processes and display.
\=============================================================================*/

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

    Camera               m_Camera;
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