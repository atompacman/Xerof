#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <math.h>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\utils\FatalErrorDialog.h"
#include "..\Parameters.h"
/*============================================================================||
| Variables about the camera controller by the mouse
|-----------------------------------------------------------------------------||
| - Hold left button to move camera
| - Hold right button to zoom
| - Wheel to zoom
\=============================================================================*/

struct Mouse
{
	int         m_State;
	double      m_Zoom;
    double      m_Rotate;
    DCoord      m_Pos;
    const Coord m_MaxPos;

	//CONSTRUCTOR/DESTRUCTOR
    Mouse(Dimensions i_MapDim, UINT i_TileSize);

	//EVENT HANDLING
	void handleMouseEvent(const ALLEGRO_EVENT& i_Event);
};