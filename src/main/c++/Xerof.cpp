#include <iomanip>
#include <stdlib.h>
#include "easylogging++.h"
#include "engine\GameLoop.h"
//********************************
#include "world\MapConfig.h"

INITIALIZE_EASYLOGGINGPP

void initLoggingLibrary();
void initGameEngine();

int main(int argc, char** argv)
{
	// Initialize easylogging++ library
	initLoggingLibrary();

    //********************************
    MapConfig();

	// Welcome message !
	LOG(INFO) <<"======-=====-====-===-==-=- XEROF -=-==-===-====-=====-======";

	// Create the world... nothing less
	World::getInstance();

	// Initialize Allegro5 library
	initGameEngine();

	// Start the game loop
    GameLoop::run();

	return EXIT_SUCCESS;
}

void initLoggingLibrary()
{
	el::Configurations conf;
	if (!conf.parseFromFile(LOGGER_CONFIG_FILE))
	{
		LOG(WARNING) << "Easylogging++ configuration file "<< LOGGER_CONFIG_FILE 
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