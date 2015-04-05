#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <math.h>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Camera.h"
#include "..\utils\FatalErrorDialog.h"
/*============================================================================||
| Variables about the camera controller by the mouse
|-----------------------------------------------------------------------------||
| - Hold left button to move camera
| - Hold right button to zoom and rotate camera
| - Wheel to zoom
\=============================================================================*/

enum MouseState {
    IDLE, 
    LEFT_BUTTON_PRESSED, 
    RIGHT_BUTTON_PRESSED
};

class Mouse
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Mouse(Camera& io_Camera);

    // EVENT HANDLING
    void handleButtonPressed(const ALLEGRO_EVENT& i_Event);
    void handleButtonReleased(const ALLEGRO_EVENT& i_Event);
    void handleCursorMoved(const ALLEGRO_EVENT& i_Event);

private:
    // The camera controlled by the mouse
    Camera&     m_Camera;

    // Current pressed button (or no button pressed)
    MouseState  m_State;

    // Last clicked tile
    bool        m_HasTileSelected;
    Coord       m_ClickedTile;

	// EVENT HANDLING
    void saveClickedTile(UINT i_x, UINT i_y);
};