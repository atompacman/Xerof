#include <iomanip>
#include <stdlib.h>
#include "easylogging++.h"
#include "engine\GameLoop.h"

INITIALIZE_EASYLOGGINGPP

// Peripherals
Display*  s_Display;
Mouse*    s_Mouse;
Keyboard* s_Keyboard;

// Game world
World* World::s_World;

void initLoggingLibrary();
void initGameEngine();

int main(int argc, char** argv)
{
	// Initialize easylogging++ library
	initLoggingLibrary();

	// Welcome message !
	LOG(INFO) << "-====-===-==-=- XEROF -=-==-===-====-";

	// Create the world... nothing less
	const World* world = World::getInstance();

	// Initialize Allegro5 library
	initGameEngine();

	// Initialize peripherals
	s_Mouse = new Mouse();
	s_Display = new Display(s_Mouse);
	s_Keyboard = new Keyboard();

	// Load assets
	s_Display->m_Assets = loadAssets();

	// Start the game loop
	GameLoop(s_Display, s_Mouse, s_Keyboard).start();

	// Free assets memory
	destroyAssets(s_Display->m_Assets);

	// Delete peripherals
	delete s_Display;
	delete s_Mouse;
	delete s_Keyboard;

	return EXIT_SUCCESS;
}

void initLoggingLibrary()
{
	el::Configurations conf;
	if (!conf.parseFromFile(LOGGER_CONFIG_FILE))
	{
		LOG(WARNING) << "Easylogging++ configuration file " << LOGGER_CONFIG_FILE << " was not found. Using default parameters.";
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