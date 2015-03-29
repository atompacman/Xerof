#pragma once
#include "allegro5\allegro.h"
#include "utils\Elem2D.h"

///////////////////////////////////////////////////////////////////////////
//  <     #     #     #     #     #     #     #     #     #     #     >  //
//                                                                       //
//  <                        XEROF PARAMETERS                         >  //
//                                                                       //
//  <     #     #     #     #     #     #     #     #     #     #     >  //
///////////////////////////////////////////////////////////////////////////

//=== - === - === - === - === - === - === - === - === - === - === - === -//
//                              LOGGING                                  //
//=== - === - === - === - === - === - === - === - === - === - === - === -//

// The path to the easylogging++ configuration file
#define LOGGER_CONFIG_FILE "logs/log_config.conf"

// Progress bar increments (ex.: 0.1 means we print every 10%)
#define PGI 0.1


//=== - === - === - === - === - === - === - === - === - === - === - === -//
//                               DISPLAY                                 //
//=== - === - === - === - === - === - === - === - === - === - === - === -//

// Available display modes are: 
//		- ALLEGRO_WINDOWED
//		- ALLEGRO_FULLSCREEN
//		- ALLEGRO_FULLSCREEN_WINDOW
//		- ALLEGRO_RESIZABLE
//		- ALLEGRO_OPENGL
//		- ALLEGRO_OPENGL_3_0
//		- ALLEGRO_DIRECT3D_INTERNAL
//		- ALLEGRO_NOFRAME
#define DISPLAY_MODE ALLEGRO_RESIZABLE

// If true, the "best" screen resolution for the current display mode will
// be selected. Warning: what is considered the "best" resolution is not
// always the one with the bigger dimensions.
#define AUTOMATIC_SCREEN_RESOLUTION false

// Screen resolution (if AUTOMATIC_SCREEN_RESOLUTION is false).
#define SCREEN_RES Coord(800, 600)

// FPS when the system is not overloaded
#define TARGET_FPS 60.0

// Zoom scales
#define MIN_ZOOM_SCALE 0.0625
#define MAX_ZOOM_SCALE 2.0

// Title of the main game window
#define WINDOW_TITLE "XEROF"

// Background color in RGB value
const int BG_COLOR[] = { 0 , 0, 0 };


//=== - === - === - === - === - === - === - === - === - === - === - === -//
//                                  MAP                                  //
//=== - === - === - === - === - === - === - === - === - === - === - === -//

// Config file paths
#define DEFAULT_MAP_CONFIG "map/DefaultConfig.json"
#define MAP_LIMITS         "map/Limits.json"


//=== - === - === - === - === - === - === - === - === - === - === - === -//
//                                ASSETS                                 //
//=== - === - === - === - === - === - === - === - === - === - === - === -//

// Resolution level:                 (64)   (32)   (16)   (8)

// Size in pixels of a tile depending on zoom level (resolution level)
const UINT TILE_SIZE[]            = { 64,    32,    16,    8    };
const double TILE_GRADIENT_SIZE[] = { 16,    8,     4,     2    };

// Resolution factors (should not be modified unless new resolutions are
// added)
const UINT	RESOLU_FACTOR[]       =	{ 1,     2,     4,     8    };
const float RESOLU_FRACTION[]     = { 1,     0.5,   0.25,  0.125};

// Upper-left corner of a texture asset depending of resolution
const Coord TEXTURE_UL_CORNERS[]  = { Coord(0,  0),
                                      Coord(96, 0),
                                      Coord(96, 48),
                                      Coord(96, 72) };

// Tile alpha gradient overlapping (can be seen as the width of the black 
// grid separating tiles)
//	- 0.0 : No overlapping
//	- 1.0 : Complete overlapping
const float ALPHA_OVERLAPPING[]   = { 0.5,   0.6,   0.7,    1.0 };


//=== - === - === - === - === - === - === - === - === - === - === - === -//
//                             CIVILIZATION                              //
//=== - === - === - === - === - === - === - === - === - === - === - === -//

#define NB_CIV      1U
#define CIV_MAX_POP 100U


//=== - === - === - === - === - === - === - === - === - === - === - === -//
//                                  AI                                   //
//=== - === - === - === - === - === - === - === - === - === - === - === -//

#define SECONDS_BETWEEN_AI_PROCESS 1.0


//=== - === - === - === - === - === - === - === - === - === - === - === -//
//                                 OTHER                                 //
//=== - === - === - === - === - === - === - === - === - === - === - === -//

// Random generator options
#define RANDOM_SEED           false
#define WORLD_GENERATION_SEED 304