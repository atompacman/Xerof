#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <list>
#include <math.h>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "DisplayInfo.h"
#include "..\utils\FatalErrorDialog.h"
#include "..\world\map\Map.h"
/*============================================================================||
| Variables about the camera controller by the mouse
|-----------------------------------------------------------------------------||
| - Hold left button to move camera
| - Hold right button to zoom and rotate camera
| - Wheel to zoom
\=============================================================================*/

#define MAX_MOVE_EVENT_FOR_CLICK 10

enum MouseState {
    IDLE,
    LEFT_BUTTON_PRESSED,
    RIGHT_BUTTON_PRESSED
};

class Mouse
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Mouse(DisplayInfo& io_DisplayInfo);

    // EVENT HANDLING
    void handlePressedButton(const ALLEGRO_EVENT& i_Event);
    void handleReleasedButton(const ALLEGRO_EVENT& i_Event);
    void handleMovedCursor(const ALLEGRO_EVENT& i_Event);

private:
    // Display information handled by this peripheral
    DisplayInfo& m_DisplayInfo;

    // The camera (extracted from DisplayInfo for quicker access)
    Camera& m_Camera;

    // Current pressed button (or no button pressed)
    MouseState m_State;

    // Used for selection clicks
    unsigned int m_MoveEventsSincePressed;

    // Last clicked tile
    Coord m_ClickedTile;

    // EVENT HANDLING
    Coord computeSelectedTile(unsigned int i_x, unsigned int i_y) const;
};