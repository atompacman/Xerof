#include <Mouse.h>
#include <Parameters.h>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Mouse::Mouse(DisplayInfo& io_DisplayInfo) :
m_DisplayInfo(io_DisplayInfo),
m_Camera(m_DisplayInfo.getCamera()),
m_State(IDLE),
m_MoveEventsSincePressed(0),
m_ClickedTile(0, 0)
{
    if (!al_install_mouse()) {
        FatalErrorDialog("Mouse installation failed.");
    }
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                               EVENT HANDLING                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Mouse::handlePressedButton(const ALLEGRO_EVENT& i_Event)
{
    // Save what button was pressed
    m_State = MouseState(i_Event.mouse.button);

    // Save the clicked tile on map
    m_ClickedTile = computeSelectedTile(i_Event.mouse.x, i_Event.mouse.y);

    // Reset the number of move events since this current event
    m_MoveEventsSincePressed = 0;
}

void Mouse::handleReleasedButton(const ALLEGRO_EVENT& i_Event)
{
    // Check if it was a selection click
    bool isLeftClick(m_State == LEFT_BUTTON_PRESSED);

    // Reset mouse state to idle
    m_State = IDLE;

    // Change selection only if mouse has not moved 
    // much since left button was pressed
    if (!isLeftClick || m_MoveEventsSincePressed > MAX_MOVE_EVENT_FOR_CLICK) {
        return;
    }

    // Set selection
    m_DisplayInfo.setSelection(m_ClickedTile);
}

void Mouse::handleMovedCursor(const ALLEGRO_EVENT& i_Event)
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
        m_Camera.zoom(i_Event.mouse.dz);
    }

    ++m_MoveEventsSincePressed;
}

Coord Mouse::computeSelectedTile(unsigned int i_x, unsigned int i_y) const
{
    // Invert camera transform
    ALLEGRO_TRANSFORM copy(m_Camera.m_Transform);
    al_invert_transform(&copy);

    // Apply matrix
    Coord selectedTile(copy.m[0][0] * i_x + copy.m[1][0] * i_y + copy.m[3][0],
                       copy.m[0][1] * i_x + copy.m[1][1] * i_y + copy.m[3][1]);

    // Divide by tile length
    selectedTile /= TILE_SIZE[m_Camera.getResolutionLvl()];

    return selectedTile;
}