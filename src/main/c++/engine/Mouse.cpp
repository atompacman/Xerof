#include "Mouse.h"
#include "internal\dialog\FatalErrorDialog.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Mouse::Mouse()
{
	if (!al_install_mouse()) {
		FatalErrorDialog("Mouse installation failed.");
	}
	zoom = 1.0;
	rotate = 0.0;
	scrollX = 0.0;
	scrollY = 0.0;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                EVENT HANDLING               //
//- - - - - - - - - - - - - - - - - - - - - - -//

void Mouse::handleMouseEvent(const ALLEGRO_EVENT& event)
{
	switch (event.type) {
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		state = event.mouse.button;
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		state = 0;
		break;
	case ALLEGRO_EVENT_MOUSE_AXES:
		if (state == 1) {
			float x = event.mouse.dx / zoom;
			float y = event.mouse.dy / zoom;
			scrollX -= x * cos(rotate) + y * sin(rotate);
			scrollY -= y * cos(rotate) - x * sin(rotate);

			scrollX = scrollX < 0 ? 0 : scrollX;
			scrollX = scrollX > maxScrollX ? maxScrollX : scrollX;
			scrollY = scrollY < 0 ? 0 : scrollY;
			scrollY = scrollY > maxScrollY ? maxScrollY : scrollY;
		}
		if (state == 2) {
			rotate += event.mouse.dx * 0.01;
			zoom -= event.mouse.dy * 0.01 * zoom;
		}
		zoom += event.mouse.dz * 0.1 * zoom;
		if (zoom < MIN_ZOOM_SCALE) {
			zoom = MIN_ZOOM_SCALE;
		}
		if (zoom > MAX_ZOOM_SCALE) {
			zoom = MAX_ZOOM_SCALE;
		}
	}
}