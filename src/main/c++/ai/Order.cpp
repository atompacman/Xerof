#include "Order.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Order::Order(PossibleOrders action, int param1, int param2, int param3)
{
	this->action = action;
	this->params = new int[3];
	params[0] = param1;
	params[1] = param2;
	params[2] = param3;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   GETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

PossibleOrders Order::getAction() const
{
	return action;
}

int* Order::getParams() const
{
	return params;
}