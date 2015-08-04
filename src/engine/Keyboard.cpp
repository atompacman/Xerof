#include "Keyboard.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Keyboard::Keyboard(DisplayInfo& io_DisplayInfo) :
m_DisplayInfo(io_DisplayInfo)
{
	if (!al_install_keyboard()) {
		FatalErrorDialog("Keyboard installation failed.");
	}
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                               EVENT HANDLING                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Keyboard::handlePressedKey(const ALLEGRO_EVENT& i_Event)
{
	m_PressedKeys[i_Event.keyboard.keycode] = true;
	return true;
}

bool Keyboard::handleReleasedKey(const ALLEGRO_EVENT& i_Event)
{
	m_PressedKeys[i_Event.keyboard.keycode] = false;

	switch (i_Event.keyboard.keycode) {
	case ALLEGRO_KEY_ESCAPE:
		return false;
	case ALLEGRO_KEY_F:
		m_DisplayInfo.switchFollowSelection();
		return true;
	default:
		break;
	}
	return true;
}

bool Keyboard::handleTypedCharacter(const ALLEGRO_EVENT& i_Event)
{
	return true;
}