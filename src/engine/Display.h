#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include "allegro5\allegro.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_native_dialog.h"
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\civ\CivController.h"
#include "Mouse.h"
/*============================================================================||
| Drawing bitmap graphics
|-----------------------------------------------------------------------------||
| Draws on screen the world and civilizations
\=============================================================================*/

class Display
{
public:
	//CONSTRUCTOR/DESTRUCTOR
    Display(const World&     i_World, 
            const Camera&    i_Camera);
	~Display();

	//DRAW
	void draw();
    void resize();

	//SETTERS
	void setCivs(CivController** i_Civ);
	void setFPS(int i_FPS);

    //GETTERS
    ALLEGRO_DISPLAY& getWindow() const;
    Coord            getWindowSize() const;

private:
    // Initialized outside
    const World&     m_World;
    const Camera&    m_Camera;

    // Initialized here
    ALLEGRO_DISPLAY&  m_Window;
    ALLEGRO_BITMAP**  m_Assets;
	ALLEGRO_FONT&     m_GameFont;

	//CONSTRUCTOR/DESTRUCTOR
    static ALLEGRO_DISPLAY& createWindow();

    // DRAW
    void drawEnvironment();
    void drawHumans();
};

static float correspondingAngle(Direction i_Dir) {
    assertNonCenterDir(i_Dir);

    switch (i_Dir) {
    case UP:			return 0;
    case UPPER_RIGHT:	return ALLEGRO_PI * 0.25;
    case RIGHT:			return ALLEGRO_PI * 0.5;
    case LOWER_RIGHT:	return ALLEGRO_PI * 0.75;
    case DOWN:			return ALLEGRO_PI * 1.0;
    case LOWER_LEFT:	return ALLEGRO_PI * 1.25;
    case LEFT:			return ALLEGRO_PI * 1.5;
    case UPPER_LEFT:	return ALLEGRO_PI * 1.75;
    }
    return 0.0;
}