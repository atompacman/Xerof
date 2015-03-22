#include "engine\GameLoop.h"
#include "easylogging++.h"
#include <stdlib.h>

INITIALIZE_EASYLOGGINGPP

// Peripherals
Display* display;
Mouse* mouse;
Keyboard* keyboard;

// Game world
World* World::world;

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
	mouse = new Mouse();
	display = new Display(mouse);
	keyboard = new Keyboard();

	// Load assets
	display->m_Assets = loadAssets();

	// Start the game loop
	GameLoop(display, mouse, keyboard).start();

	// Free assets memory
	destroyAssets(display->m_Assets);

	// Delete peripherals
	delete display;
	delete mouse;
	delete keyboard;

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