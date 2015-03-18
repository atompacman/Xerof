#include "Keyboard.h"
#include "dialog\FatalErrorDialog.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Keyboard::Keyboard()
{
	if (!al_install_keyboard()) {
		FatalErrorDialog("Keyboard installation failed.");
	}
}