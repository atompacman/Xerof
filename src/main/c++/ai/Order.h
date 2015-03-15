#pragma once
#include <stdarg.h>

enum PossibleOrders
{
	WALK
};

class Order
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	Order(PossibleOrders action, int param1 = -1, int param2 = -1, int param3 = -1);

	// GETTERS
	PossibleOrders getAction() const;
	int* getParams() const;

private:
	PossibleOrders action;
	int* params;
};