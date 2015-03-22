#include "Order.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Order::Order(PossibleOrders i_Action, int i_Param1, int i_Param2, int i_Param3)
{
    this->m_Action = i_Action;
	this->m_Params = new int[3];
	m_Params[0] = i_Param1;
	m_Params[1] = i_Param2;
	m_Params[2] = i_Param3;
}