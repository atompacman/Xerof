#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Display.h"
#include "DisplayInfo.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "..\world\World.h"
/*============================================================================||
| The main class of the game
|-----------------------------------------------------------------------------||
| Handle the event queue. Manages processes and display.
\=============================================================================*/

class CivController;
class HumanPerception;
class MoveProcess;
class Order;
enum  PossibleOrders;

class GameLoop
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    GameLoop();
    ~GameLoop();

    // START
    void startGame();

private:
    World           m_World;
    CivController** m_CivCtrls;

    DisplayInfo m_DisplayInfo;
    Mouse       m_Mouse;
    Keyboard    m_Keyboard;
    Display     m_Disp;

    ALLEGRO_EVENT_QUEUE* m_Queue;
    ALLEGRO_TIMER*       m_ScreenRefresher;

    unsigned int          m_NumMoveProcs;
    MoveProcess** m_MoveProcs;

    // CONSTRUCTOR/DESTRUCTOR
    CivController** initCivCtrls();

    // UPDATE
    void updateGame();
    void processAI();
    void processOrder(HumanInfo& io_Human, const Order& i_Order);
    void processMovingOrder(HumanInfo&     io_Human,
                            PossibleOrders i_Action,
                            Direction      i_Dir);
    bool verifyDestination(const Position& i_Dest) const;
    bool isOccupied(Coord i_Coord) const;
    void updateMovements();

    // END
    void endProcesses();
};