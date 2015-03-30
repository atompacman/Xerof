#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include "allegro5\allegro.h"
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "utils\Elem2D.h"
/*============================================================================||
| Xerof parameters
|-----------------------------------------------------------------------------||
| Different category of parameters
\=============================================================================*/

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                             CIVILIZATION                                   //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

#define NB_CIV      1
#define CIV_MAX_POP 100


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                              LOGGING                                       //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

// The path to the easylogging++ configuration file
#define LOGGER_CONFIG_FILE "logs/log_config.conf"

// Progress bars increments (ex.: 0.1 means we print every 10%)
#define PGI 0.1


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                              DISPLAY                                       //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

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

// Target FPS
#define TARGET_FPS 60.0

// Zoom scales
#define MIN_ZOOM_SCALE 0.0625
#define MAX_ZOOM_SCALE 2.0

// Title of the main game window
#define WINDOW_TITLE "XEROF"

// Background color in RGB value
const int BG_COLOR[] = { 0 , 0, 0 };


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                  MAP                                       //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

// Config file paths
#define DEFAULT_MAP_CONFIG "map/DefaultConfig.json"
#define MAP_LIMITS         "map/Limits.json"


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                  AI                                        //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

#define SECONDS_BETWEEN_AI_PROCESS 1.0


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                              RANDOM                                        //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

// Random generator options
#define RANDOM_SEED           false
#define WORLD_GENERATION_SEED 304