#pragma once
#include <assert.h>
#include <wtypes.h>

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
    PossibleOrders getAction() const;
    int            getParam(UINT i_ID) const;

private:
	PossibleOrders m_Action;
	int            m_Params[3];
};