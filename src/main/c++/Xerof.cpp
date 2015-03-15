#include "engine\GameLoop.h"
#include <stdlib.h>

Display* display;
Mouse* mouse;
Keyboard* keyboard;

World* World::world;

bool initializePeripherals();
void shutdownPeripherals();

int main(int argc, char **argv) 
{
	if (DEBUG_MODE) {
		fprintf(stdout, "XEROF\n");
	}

	const World* world = World::getInstance();

	if (initializePeripherals()) {
		return EXIT_FAILURE;
	}

	if (loadAssets()) {
		return EXIT_FAILURE;
	}

	display->setAssets(assets);

	GameLoop gameLoop = GameLoop(display, mouse, keyboard);
	if (gameLoop.initFailed()) {
		return EXIT_FAILURE;
	}

	gameLoop.start();

	shutdownPeripherals();
	destroyAssets();
	return EXIT_SUCCESS;
}

bool initializePeripherals()
{
	display = new Display();
	if (display->initFailed()) {
		return EXIT_FAILURE;
	}

	mouse = new Mouse();
	if (mouse->initFailed()) {
		return EXIT_FAILURE;
	}

	display->setMouse(mouse);

	keyboard = new Keyboard();
	if (keyboard->initFailed()) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void shutdownPeripherals() 
{
	delete display;
	delete mouse;
	delete keyboard;
}