#pragma once

/*============================================================================\\
| The message that AIs sends to CivControllers
|-----------------------------------------------------------------------------||
| The order represents a concrete action that a Human can make on its
| environment.
\=============================================================================*/

enum Action
{
    WALK
};

class Order
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Order(Action i_Action, 
         int     i_Param1 = -1,
         int     i_Param2 = -1,
         int     i_Param3 = -1);

    // GETTERS
    Action getAction() const;
    int    getParam(unsigned int i_ID) const;

private:
    Action m_Action;
    int    m_Params[3];
};