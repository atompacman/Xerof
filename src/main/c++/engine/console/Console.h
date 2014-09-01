#pragma once
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include "..\world\Tile.h"
#include "..\world\World.h"

const unsigned int HORIZ_BORDER_LENGTH = 2;
const unsigned int VERT_BORDER_LENGTH = 1;

const unsigned int X_CONSOLE_SIZE = MAP_LENGTH + HORIZ_BORDER_LENGTH * 2;
const unsigned int Y_CONSOLE_SIZE = MAP_HEIGHT + VERT_BORDER_LENGTH * 2;

class Console
{
public:
	//CONSTRUCTOR/DESCTRUCTOR
	Console();
	~Console(){};

	//PRINT MAP
	void printWorld(const World& world) const;

private:
	HANDLE consoleHandle;

	//PRINT MAP
	unsigned char colorCodeFor(const Tile& tile, bool isNight) const;
	char characterFor(const Tile& tile) const;
};