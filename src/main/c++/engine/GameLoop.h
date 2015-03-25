#pragma once
#include "allegro5\allegro.h"
#include "..\ai\AtomAI.h"
#include "Display.h"
#include "Keyboard.h"
#include "MoveProcess.h"

class GameLoop
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	GameLoop(Display* i_Disp, Mouse* i_Mouse, Keyboard* i_Key);
	~GameLoop();

	// START
	bool start();

private:
	ALLEGRO_EVENT_QUEUE* m_Queue;
	ALLEGRO_TIMER*       m_ScreenRefresher;

	CivController**      m_CivCtrlrs;
	AI**                 m_AIs;
	
	int                  m_NumMoveProcs;
	MoveProcess**        m_MoveProcs;

	Display*             m_Disp;
	Mouse*               m_Mouse;
	Keyboard*            m_Keyboard;
	ALLEGRO_BITMAP**     m_Assets;

    // CONSTRUCTOR/DESTRUCTOR
    void initializeCivsAndAIs();

	// UPDATE
	bool updateGame();
	bool processAI();
    bool processOrder(Human* io_Human, const Order& i_Order);
    bool processMovingOrder(Human* i_Human,
                            PossibleOrders i_Action,
                            Direction i_Dir);
    bool verifyDestination(const Position& i_Dest) const;
    bool isOccupied(Coord<int> i_Coord) const;

	// UPDATE ANIMATIONS
	void updateMovements();

	// END
	void endProcesses();
};