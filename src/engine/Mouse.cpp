#include "Mouse.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Mouse::Mouse(Camera& io_Camera) :
m_Camera(io_Camera),
m_State(IDLE),
m_HasTileSelected(false),
m_ClickedTile(0,0)
{
	if (!al_install_mouse()) {
		FatalErrorDialog("Mouse installation failed.");
	}
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                               EVENT HANDLING                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Mouse::handleButtonPressed(const ALLEGRO_EVENT& i_Event)
{
    m_State = MouseState(i_Event.mouse.button);

    // If it is a normal click, save the clicked tile coordinate on map
    if (m_State == LEFT_BUTTON_PRESSED) {
        saveClickedTile(i_Event.mouse.x, i_Event.mouse.y);
    }
}

void Mouse::handleButtonReleased(const ALLEGRO_EVENT& i_Event)
{
    m_State = IDLE;
}

void Mouse::handleCursorMoved(const ALLEGRO_EVENT& i_Event)
{
    switch (m_State) {
    case LEFT_BUTTON_PRESSED:
        m_Camera.translate(DCoord(i_Event.mouse.dx, i_Event.mouse.dy));
        break;

    case RIGHT_BUTTON_PRESSED:
        m_Camera.rotateAndZoom(DCoord(i_Event.mouse.dx, i_Event.mouse.dy));
        break;

    default:
        break;
    }

    // Scrollwheel zoom
    if (i_Event.mouse.dz != 0) {
        m_Camera.scrollwheelZoom(i_Event.mouse.dz);
    }
}

void Mouse::saveClickedTile(UINT i_x, UINT i_y)
{

}