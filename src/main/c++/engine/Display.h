#pragma once
#include "allegro5\allegro.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_native_dialog.h"
#include "..\civilization\CivController.h"
#include "Mouse.h"

static Dimensions maxBufferDimensions() {
	return MAP_DIMENSIONS * (int) TILE_SIZE[0];
}

static float correspondingAngle(Direction direction) {
	assert(direction != MIDDLE);

	switch (direction) {
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

class Display
{
public:
	ALLEGRO_DISPLAY* window;

	//CONSTRUCTOR/DESCTRUCTOR
	Display(Mouse* a_Mouse, ALLEGRO_BITMAP** a_Assets);
	~Display();

	//DRAW
	void draw() const;

	//SETTERS
	void setCivs(CivController**);
	void setFPS(int fps);

private:
	ALLEGRO_BITMAP** m_Assets;
	ALLEGRO_FONT* gameFont;
	CivController** civilizations;
	Mouse* m_Mouse;

	//CONSTRUCTOR/DESCTRUCTOR
	bool createWindow();
	void loadGameIcon();
	void loadGameFont();
	
	//DRAW
	int resolutionLevel() const;
	void actualFieldOfView(float actualWidth, float actualHeight, int* values) const;
};