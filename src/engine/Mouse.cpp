#include "Mouse.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Mouse::Mouse(Dimensions i_MapDim, UINT i_TileSize) :
m_State(0),
m_Zoom(1.0),
m_Rotate(0),
m_Pos(toDCoord(i_MapDim * i_TileSize) * 0.5),
m_MaxPos(i_MapDim * i_TileSize)
{
	if (!al_install_mouse()) {
		FatalErrorDialog("Mouse installation failed.");
	}
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                               EVENT HANDLING                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Mouse::handleMouseEvent(const ALLEGRO_EVENT& i_Event)
{
	switch (i_Event.type) {
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		m_State = i_Event.mouse.button;
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		m_State = 0;
		break;
	case ALLEGRO_EVENT_MOUSE_AXES:
		if (m_State == 1) {
			double x = i_Event.mouse.dx / m_Zoom;
            double y = i_Event.mouse.dy / m_Zoom;
            m_Pos.x -= x * cos(m_Rotate) + y * sin(m_Rotate);
            m_Pos.y -= y * cos(m_Rotate) - x * sin(m_Rotate);
            m_Pos.x = max(0, min(m_Pos.x, m_MaxPos.x));
            m_Pos.y = max(0, min(m_Pos.y, m_MaxPos.y));
		}
		if (m_State == 2) {
			m_Rotate += i_Event.mouse.dx * 0.01;
			m_Zoom -= i_Event.mouse.dy * 0.01 * m_Zoom;
		}
		m_Zoom += i_Event.mouse.dz * 0.1 * m_Zoom;
        m_Zoom = max(MIN_ZOOM_SCALE, min(m_Zoom, MAX_ZOOM_SCALE));
	}
}