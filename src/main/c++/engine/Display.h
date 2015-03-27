#pragma once
#include "allegro5\allegro.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_native_dialog.h"
#include "..\civilization\CivController.h"
#include "Mouse.h"

class Display
{
public:
	//CONSTRUCTOR/DESTRUCTOR
	Display(Mouse* i_Mouse);
	~Display();

	//DRAW
	void draw() const;
    void resize() const;

	//SETTERS
	void setCivs(CivController** i_Civ);
	void setFPS(int i_FPS);

    //GETTERS
    ALLEGRO_DISPLAY* getWindow() const;

private:
    ALLEGRO_DISPLAY* m_Window;
    ALLEGRO_BITMAP** m_Assets;
	ALLEGRO_FONT*    m_GameFont;
	CivController**  m_Civs;
	Mouse*           m_Mouse;

	//CONSTRUCTOR/DESTRUCTOR
    static ALLEGRO_DISPLAY* createWindow();
	
	//DRAW
	int resolutionLevel() const;
	void actualFieldOfView(float i_ActualWidth, float i_ActualHeight, UINT* i_Values) const;
};

static float correspondingAngle(Direction i_Dir) {
    assert(i_Dir != MIDDLE);

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