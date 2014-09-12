#pragma once
#include "..\Parameters.h"
#include "Initializable.h"
#include <math.h>

class Mouse: public Initializable
{
public:
	int state;
	float zoom;
	float rotate;
	float scrollX, scrollY;
	float maxScrollX, maxScrollY;

	//CONSTRUCTOR/DESCTRUCTOR
	Mouse();

	//EVENT HANDLING
	void handleMouseEvent(const ALLEGRO_EVENT&);
};