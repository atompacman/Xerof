#pragma once
#include <stdarg.h>

enum PossibleOrders
{
	WALK
};

class Order
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	Order(PossibleOrders i_Action, 
          int            i_Param1 = -1, 
          int            i_Param2 = -1, 
          int            i_Param3 = -1);

	// GETTERS
    PossibleOrders getAction() const { return m_Action; };
    int* getParams() const { return m_Params; };

private:
	PossibleOrders m_Action;
	int* m_Params;
};