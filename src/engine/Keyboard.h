#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Camera.h"
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
	Keyboard(Camera& io_Camera);

	// EVENT HANDLING
	bool handlePressedKey(const ALLEGRO_EVENT& i_Event);
	bool handleReleasedKey(const ALLEGRO_EVENT& i_Event);
	bool handleTypedCharacter(const ALLEGRO_EVENT& i_Event);

private:
	// The camera
	Camera& m_Camera;

	// Vector of pressed keys
	bool m_PressedKeys[ALLEGRO_KEY_MAX];
};