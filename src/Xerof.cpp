//===========================================================================\\
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#define ELPP_DEFAULT_LOG_FILE "logs/xerof.log"
#include "easylogging++.h"
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "engine\GameLoop.h"
#include "civ\human\RangeOfSight.h"
/*============================================================================||
| Main entry point of the game
|-----------------------------------------------------------------------------||
| Initializes libraries before launching the game loop
\=============================================================================*/

INITIALIZE_EASYLOGGINGPP

void initLoggingLibrary();
void initGameEngine();

int main(int argc, char** argv)
{
    // Initialize easylogging++ library
    initLoggingLibrary();

    // Welcome message !
    LOG(INFO) <<"======-=====-====-===-==-=- XEROF -=-==-===-====-=====-======";

    // Initialize Allegro5 library
    initGameEngine();

    // Initialize random seed
    initRandSeed();

    // Start the game loop
    GameLoop().startGame();

    return EXIT_SUCCESS;
}

void initLoggingLibrary()
{
    el::Configurations conf;
    if (!conf.parseFromFile(LOGGER_CONFIG_FILE))
    {
        LOG(WARNING) << "Easylogging++ configuration file " << LOGGER_CONFIG_FILE
            << " was not found. Using default parameters.";
    }
    el::Loggers::reconfigureAllLoggers(conf);
}

void initGameEngine()
{
    if (!al_init()) {
        FatalErrorDialog("Allegro 5 core library initialization failed.");
    }
    if (!al_init_image_addon()){
        FatalErrorDialog("Allegro image add-on initialization failed.");
    }
    if (!al_init_primitives_addon()){
        FatalErrorDialog("Allegro primitives add-on initialization failed.");
    }
}