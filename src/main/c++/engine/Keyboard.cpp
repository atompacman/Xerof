#include "Keyboard.h"
#include "internal\dialog\FatalErrorDialog.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Keyboard::Keyboard()
{
	if (!al_install_keyboard()) {
		FatalErrorDialog("Keyboard installation failed.");
	}
}