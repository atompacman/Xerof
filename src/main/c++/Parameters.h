#pragma once
#include "allegro5\allegro.h"
#include "world\Coord.h"

///////////////////////////////////////////////////////////////////////////
//  <     #     #     #     #     #     #     #     #     #     #     >  //
//                                                                       //
//  <                        XEROF PARAMETERS                         >  //
//                                                                       //
//  <     #     #     #     #     #     #     #     #     #     #     >  //
///////////////////////////////////////////////////////////////////////////

//=== - === - === - === - === - === - === - === - === - === - === - === -//
//                              Debugging                                //
//=== - === - === - === - === - === - === - === - === - === - === - === -//

// Prints information about the internal system in the console.
const bool DEBUG_MODE = true;

// Verbose (REMOVE ME)
#define VERBOSE 3

// The path to the easylogging++ configuration file
#define LOGGER_CONFIG_FILE "logs/log_config.conf"


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
const int DISPLAY_MODE = ALLEGRO_RESIZABLE;

// If true, the "best" screen resolution for the current display mode will
// be selected. Warning: what is considered the "best" resolution is not
// always the one with the bigger dimensions.
const bool AUTOMATIC_SCREEN_RESOLUTION = false;

// Screen resolution (if AUTOMATIC_SCREEN_RESOLUTION is false).
const int RESOLUTION_WIDTH = 800; //1920
const int RESOLUATION_HEIGHT = 600; //1080

// FPS when the system is not overloaded
const float TARGET_FPS = 60.0;

// Zoom scales
static const float MIN_ZOOM_SCALE = 0.0625;
static const float MAX_ZOOM_SCALE = 2.0;

// Title of the main game window
static const char* WINDOW_TITLE = "XEROF";

// Background color in RGB value
const int BG_COLOR[] = { 0 , 0, 0 };


//=== - === - === - === - === - === - === - === - === - === - === - === -//
//                            MAP GENERATION                             //
//=== - === - === - === - === - === - === - === - === - === - === - === -//
// Width X Height
const Dimensions MAP_DIMENSIONS = Dimensions(300, 200); // (128, 96)

// Land proportion
const float LAND_PROPORTION_2 = 0.6;

// Quantity of initial land tiles before growing the islands
//		- 0.001  = pangea
//		- 0.01   = continents
//		- 0.1    = archipelago
const float INITIAL_LAND_TILES_2 = 0.01;

//		- 0.1 = very dispersed 
//		- 0.5 = normal
//		- 1.5 = concentrated in the middle
const float LAND_DISPERTION = 0.5;

//   - 0.1 = very fractal
//   - 1.0 = irregular
//   - 2.0 = completely full
const float LANDMASS_COMPACTNESS = 1.0;

// If this is 0.1, it means that every 10%, a message will appear on the
// console to indicate the progression of the map generation.
const float PROGRESSION_INCREMENTS_PERC = 0.1;

// Minimal width between land and map borders
const unsigned int OCEAN_MARGINS = 1;


//=== - === - === - === - === - === - === - === - === - === - === - === -//
//                                ASSETS                                 //
//=== - === - === - === - === - === - === - === - === - === - === - === -//
// Resolution level:               (64)   (32)   (16)   (8)

// Size in pixels of a tile depending on zoom level (resolution level)
const float TILE_SIZE[] =		  { 64,    32,    16,    8    };
const float TILE_GRADIENT_SIZE[]= { 16,    8,     4,     2    };

// Resolution factors (should not be modified unless new resolutions are
// added)
const int	RESOLU_FACTOR[] =	  { 1,     2,     4,     8    };
const float RESOLU_FRACTION[] =   { 1,     0.5,   0.25,  0.125};

// Upper-left corner of a texture asset depending of resolution
const float TEXTURE_CORNER_X[] =  { 0,     96,    96,    96   };
const float TEXTURE_CORNER_Y[] =  { 0,     0,     48,    72   };

// Tile alpha gradient overlapping (can be seen as the width of the black 
// grid separating tiles)
//	- 0.0 : No overlapping
//	- 1.0 : Complete overlapping
const float ALPHA_OVERLAPPING[] = { 0.5,   0.6,   0.7,    1.0 };


//=== - === - === - === - === - === - === - === - === - === - === - === -//
//                             CIVILIZATION                              //
//=== - === - === - === - === - === - === - === - === - === - === - === -//

const unsigned int NB_CIV = 1;
const unsigned int MAX_POPULATION = 100;


//=== - === - === - === - === - === - === - === - === - === - === - === -//
//                                  AI                                   //
//=== - === - === - === - === - === - === - === - === - === - === - === -//
const float SECONDS_BETWEEN_AI_PROCESS = 1.0;


//=== - === - === - === - === - === - === - === - === - === - === - === -//
//                                 OTHER                                 //
//=== - === - === - === - === - === - === - === - === - === - === - === -//

// Random generator options
const static bool RANDOM_SEED = false;
const static unsigned int WORLD_GENERATION_SEED = 304;