#include "Mouse.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Mouse::Mouse(Camera& io_Camera, Map& i_Map) :
m_Camera(io_Camera),
m_SelHuman(NULL),
m_State(IDLE),
m_MoveEventsSincePressed(0),
m_ClickedTile(0,0),
m_Map(i_Map)
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

    // If clicked tile is out of the map, clear selection
    if (!(m_ClickedTile < (m_Camera.m_MaxPos / TILE_SIZE[0]))) {
        clearSelection();
        return;
    }

    // Get selected human
    HumanInfo* currSelect(m_Map.getTile(m_ClickedTile).getHuman());

    // If there is no human on selected tile or if its the selected
    // one, clear selection
    if (currSelect == NULL || currSelect == m_SelHuman) {
        clearSelection();
        return;
    }

    // Finaly, we can do our new selection !
    clearSelection();
    currSelect->select();
    m_SelHuman = currSelect;
}

void Mouse::clearSelection()
{
    if (m_SelHuman != NULL) {
        m_SelHuman->unselect();
        m_SelHuman = NULL;
    }
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
        m_Camera.scrollwheelZoom(i_Event.mouse.dz);
    }

    ++m_MoveEventsSincePressed;
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
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Camera& Mouse::getCamera() const
{
    return m_Camera;
}

Camera& Mouse::getCamera()
{
    return m_Camera;
}

const HumanInfo& Mouse::getSelectedHuman() const
{
    return *m_SelHuman;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   SETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Mouse::setSelectedHuman(HumanInfo* i_Human)
{
    m_SelHuman = i_Human;
    i_Human->select();
    m_Camera.setPosition(i_Human->getPos().coord());
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     STATE                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Mouse::hasSelectedHuman() const
{
    return m_SelHuman != NULL;
}