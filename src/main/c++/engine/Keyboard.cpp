#include "Keyboard.h"
#include "internal\dialog\FatalErrorDialog.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Keyboard::Keyboard()
{
	if (!al_install_keyboard()) {
		FatalErrorDialog("Keyboard installation failed.");
	}
}