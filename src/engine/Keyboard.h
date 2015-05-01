#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "DisplayInfo.h"
#include "..\utils\FatalErrorDialog.h"
/*============================================================================||
| Keyboard
|-----------------------------------------------------------------------------||
| Event handling methods return "false" to exit the game
\=============================================================================*/

class Keyboard
{
public:
	//CONSTRUCTOR/DESTRUCTOR
	Keyboard(DisplayInfo& io_DisplayInfo);

	// EVENT HANDLING
	bool handlePressedKey(const ALLEGRO_EVENT& i_Event);
	bool handleReleasedKey(const ALLEGRO_EVENT& i_Event);
	bool handleTypedCharacter(const ALLEGRO_EVENT& i_Event);

private:
	// Display information handled by this peripheral
	DisplayInfo& m_DisplayInfo;

	// Vector of pressed keys
	bool m_PressedKeys[ALLEGRO_KEY_MAX];
};