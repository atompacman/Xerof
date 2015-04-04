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

// Size in pixels of a tile depending on zoom level (resolution level)
static const UINT   TILE_SIZE[]          = { 64,  32,  16,   8     };
static const double TILE_GRADIENT_SIZE[] = { 16,  8,   4,    2     };

// Resolution factors (should not be modified unless new resolutions are added)
static const UINT	RESOLU_FACTOR[]      = { 1,   2,   4,    8     };
static const float  RESOLU_FRACTION[]    = { 1,   0.5, 0.25, 0.125 };

// Tile alpha gradient overlapping (can be seen as the width of the black 
// grid separating tiles)
//	- 0.0 : No overlapping
//	- 1.0 : Complete overlapping
static const float  ALPHA_OVERLAPPING[]  = { 0.5, 0.6, 0.7,  1.0   };

// Upper-left corner of a texture asset depending of resolution
static const Coord TEXTURE_UL_CORNERS[] = { Coord(0, 0),
                                            Coord(96, 0),
                                            Coord(96, 48),
                                            Coord(96, 72) };

class Display
{
public:
	//CONSTRUCTOR/DESTRUCTOR
    Display(const World&    i_World, 
            const Mouse&    i_Mouse, 
            CivController** i_Civs);
	~Display();

	//DRAW
	void draw();
    void resize() const;

	//SETTERS
	void setCivs(CivController** i_Civ);
	void setFPS(int i_FPS);

    //GETTERS
    ALLEGRO_DISPLAY& getWindow() const;

private:
    // Initialized outside
    const World&    m_World;
    const Mouse&    m_Mouse;
    CivController** m_Civs;

    // Initialized here
    ALLEGRO_DISPLAY&  m_Window;
    ALLEGRO_BITMAP**  m_Assets;
	ALLEGRO_FONT&     m_GameFont;

    // Tiles in screen
    Coord m_ULtiles;
    Coord m_LRtiles;

	//CONSTRUCTOR/DESTRUCTOR
    static ALLEGRO_DISPLAY& createWindow();
	
	//DRAW
	int resolutionLevel();
    void updateTilesToDisplay(DDimensions i_ScreenDim);
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