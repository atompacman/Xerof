#pragma once

/*============================================================================||
| Abstract class setting the framwork for AIs
|-----------------------------------------------------------------------------||
| Currently, the only thing an AI can do is give an Order to a Human. AIs
| only knows what the Human knows.
\=============================================================================*/

class WorldPerception;
class Order;

class AI
{
public:
    // MOVE HUMAN
    virtual Order giveOrder(const WorldPerception& i_Percep) = 0;
};