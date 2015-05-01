#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <list>
#include <math.h>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Camera.h"
#include "..\utils\FatalErrorDialog.h"
#include "..\civ\human\HumanInfo.h"
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
	Mouse(Camera& io_Camera, Map& i_Map);

    // EVENT HANDLING
    void handlePressedButton(const ALLEGRO_EVENT& i_Event);
    void handleReleasedButton(const ALLEGRO_EVENT& i_Event);
    void handleMovedCursor(const ALLEGRO_EVENT& i_Event);

    // GETTERS
    const Camera&    getCamera() const;
    Camera&          getCamera();
    const HumanInfo& getSelectedHuman() const;

    // SETTERS
    void setSelectedHuman(HumanInfo* i_Human);

    // STATE
    bool hasSelectedHuman() const;

private:
    // The camera
    Camera& m_Camera;

    // Selected human
    HumanInfo* m_SelHuman;

    // Current pressed button (or no button pressed)
    MouseState m_State;

    // Used for selection clicks
    UINT m_MoveEventsSincePressed;

    // Last clicked tile
    Coord m_ClickedTile;

    // Map reference
    Map& m_Map;

	// EVENT HANDLING
    Coord computeSelectedTile(UINT i_x, UINT i_y) const;
    void clearSelection();
};