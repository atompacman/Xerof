#include "Keyboard.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Keyboard::Keyboard()
{
	initSuccess = al_install_keyboard();
	if (!initSuccess) {
		FatalErrorDialog("Keyboard installation failed.");
	}
}