#include "Mouse.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Mouse::Mouse(Camera& io_Camera) :
m_Camera(io_Camera),
m_State(IDLE),
m_HasSelectedTile(false),
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
    // Save what button was pressed
    m_State = MouseState(i_Event.mouse.button);

    // Save the clicked tile on map
    m_ClickedTile = computeSelectedTile(i_Event.mouse.x, i_Event.mouse.y);
}

void Mouse::handleButtonReleased(const ALLEGRO_EVENT& i_Event)
{
    // If cursor stayed on the same tile than at the time of the click, the
    // tile is selected
    m_HasSelectedTile = m_State == LEFT_BUTTON_PRESSED &&
        m_ClickedTile == computeSelectedTile(i_Event.mouse.x,i_Event.mouse.y) &&
        m_ClickedTile.x < m_Camera.m_MaxPos.x / TILE_SIZE[0] &&
        m_ClickedTile.y < m_Camera.m_MaxPos.y / TILE_SIZE[0];

    // Reset mouse state to idle
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

Coord Mouse::computeSelectedTile(UINT i_x, UINT i_y) const
{
    // Invert camera transform
    ALLEGRO_TRANSFORM copy(m_Camera.m_Transform);
    al_invert_transform(&copy);

    // Apply matrix
    Coord selectedTile(copy.m[0][0] * i_x + copy.m[1][0] * i_y + copy.m[3][0],
                       copy.m[0][1] * i_x + copy.m[1][1] * i_y + copy.m[3][1]);

    // Divide by tile length
    selectedTile /= m_Camera.getTileSize();

    return selectedTile;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                SELECTED TILE                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Coord Mouse::getSelectedTile() const
{
    return m_ClickedTile;
}

bool Mouse::hasSelectedTile() const
{
    return m_HasSelectedTile;
}