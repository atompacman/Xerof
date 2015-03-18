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

	// Initialize Allegro5 library
	initGameEngine();

	// Create the world... nothing less
	const World* world = World::getInstance();

	// Load assets
	if (loadAssets()) {
		return EXIT_FAILURE;
	}

	// Initialize peripherals
	mouse = new Mouse();
	display = new Display(mouse, assets);
	keyboard = new Keyboard();

	// Start the game loop
	GameLoop(display, mouse, keyboard).start();

	// Delete peripherals
	delete display;
	delete mouse;
	delete keyboard;

	// Free asset memory
	destroyAssets();

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

// Shortcuts for formatted logging
template <typename T, typename... Args>
void LOG_TRACE_F(const char* format, const T& value, const Args&... args)
{
	el::Loggers::getLogger("default")->trace(format, value, args...);
}

template <typename T, typename... Args>
void LOG_WARNING_F(const char* format, const T& value, const Args&... args)
{
	el::Loggers::getLogger("default")->warn(format, value, args...);
}

template <typename T, typename... Args>
void LOG_DEBUG_F(const char* format, const T& value, const Args&... args)
{
	el::Loggers::getLogger("default")->debug(format, value, args...);
}

template <typename T, typename... Args>
void LOG_INFO_F(const char* format, const T& value, const Args&... args)
{
	el::Loggers::getLogger("default")->info(format, value, args...);
}

template <typename T, typename... Args>
void LOG_FATAL_F(const char* format, const T& value, const Args&... args)
{
	el::Loggers::getLogger("default")->fatal(format, value, args...);
}