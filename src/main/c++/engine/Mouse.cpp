#include "Mouse.h"
#include "internal\dialog\FatalErrorDialog.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Mouse::Mouse():
m_State(0),
m_Zoom(1.0),
m_Rotate(0),
m_ScrollX(maxBufferDimensions().x / 2),
m_ScrollY(maxBufferDimensions().y / 2),
m_MaxScrollX(maxBufferDimensions().x),
m_MaxScrollY(maxBufferDimensions().y)
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
			float x = i_Event.mouse.dx / m_Zoom;
			float y = i_Event.mouse.dy / m_Zoom;
			m_ScrollX -= x * cos(m_Rotate) + y * sin(m_Rotate);
			m_ScrollY -= y * cos(m_Rotate) - x * sin(m_Rotate);

			m_ScrollX = m_ScrollX < 0 ? 0 : m_ScrollX;
			m_ScrollX = m_ScrollX > m_MaxScrollX ? m_MaxScrollX : m_ScrollX;
			m_ScrollY = m_ScrollY < 0 ? 0 : m_ScrollY;
			m_ScrollY = m_ScrollY > m_MaxScrollY ? m_MaxScrollY : m_ScrollY;
		}
		if (m_State == 2) {
			m_Rotate += i_Event.mouse.dx * 0.01;
			m_Zoom -= i_Event.mouse.dy * 0.01 * m_Zoom;
		}
		m_Zoom += i_Event.mouse.dz * 0.1 * m_Zoom;
		if (m_Zoom < MIN_ZOOM_SCALE) {
			m_Zoom = MIN_ZOOM_SCALE;
		}
		if (m_Zoom > MAX_ZOOM_SCALE) {
			m_Zoom = MAX_ZOOM_SCALE;
		}
	}
}