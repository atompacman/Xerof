#pragma once
#include <math.h>
#include "..\utils\FatalErrorDialog.h"
#include "..\Parameters.h"

struct Mouse
{
	int         m_State;
	double      m_Zoom;
    double      m_Rotate;
    DCoord      m_Pos;
    const Coord m_MaxPos;

	//CONSTRUCTOR/DESTRUCTOR
	Mouse(Dimensions i_MapDim);

	//EVENT HANDLING
	void handleMouseEvent(const ALLEGRO_EVENT& i_Event);
};