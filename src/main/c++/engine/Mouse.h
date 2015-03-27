#pragma once
#include <math.h>
#include "..\Parameters.h"

class Mouse
{
public:
	int  m_State;
	float m_Zoom;
	float m_Rotate;
	float m_ScrollX, m_ScrollY;
	const float m_MaxScrollX, m_MaxScrollY;

	//CONSTRUCTOR/DESTRUCTOR
	Mouse();

	//EVENT HANDLING
	void handleMouseEvent(const ALLEGRO_EVENT& i_Event);
};