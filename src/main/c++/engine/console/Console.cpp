#include "Console.h"


//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Console::Console()
{
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD mapSize;
	mapSize.X = X_CONSOLE_SIZE;
	mapSize.Y = Y_CONSOLE_SIZE;
	SMALL_RECT screenShape;
	screenShape.Top = 0;
	screenShape.Left = 0;
	screenShape.Right = mapSize.X - 1;
	screenShape.Bottom = mapSize.Y - 1;

	SetConsoleTitle("XEROF");

	if (!SetConsoleScreenBufferSize(consoleHandle, mapSize)) {
		std::cout << "Failure in setting screen buffer size. Please make sure that "
			<< "the size of the map does not exceed maximum screen size.";
		exit(EXIT_FAILURE);
	}
	if (!SetConsoleWindowInfo(consoleHandle, TRUE, &screenShape)) {
		std::cout << "Failure in setting window size. Please make sure that "
			<< " the size of the map does not exceed maximum screen size.";
		exit(EXIT_FAILURE);
	}
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                 PRINT MAP                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

void Console::printWorld(const World& world) const
{
	system("cls");
	SetConsoleTextAttribute(consoleHandle, 0);
	for (int y = 0; y < VERT_BORDER_LENGTH; ++y) {
		std::cout << std::endl;
	}

	for (int y = 0; y < MAP_HEIGHT; ++y) {
		SetConsoleTextAttribute(consoleHandle, 0);
		std::cout << std::string(HORIZ_BORDER_LENGTH, ' ');
		for (int x = 0; x < MAP_LENGTH; ++x) {
			Tile tile = world.map.getTile(x, y);
			SetConsoleTextAttribute(consoleHandle, colorCodeFor(tile, world.isNight()));
			std::cout << characterFor(tile);
		}
		SetConsoleTextAttribute(consoleHandle, 0);
		std::cout << std::string(HORIZ_BORDER_LENGTH, ' ');
	}
	SetConsoleTextAttribute(consoleHandle, 0);
	for (int y = 0; y < VERT_BORDER_LENGTH - 1; ++y) {
		std::cout << std::endl;
	}
}

unsigned char Console::colorCodeFor(const Tile& tile, bool isNight) const
{
	assert(tile.hasBackground());
	const Background* back = tile.getBackground();
	unsigned char code = back->color(isNight) << 4;
	if (tile.hasForeground()) {
		code += tile.getForeground()->color(isNight);
	}
	return code;
}

char Console::characterFor(const Tile& tile) const
{
	if (tile.hasForeground()) {
		return tile.getForeground()->character();
	}
	else {
		return ' ';
	}
}

int main()
{
	World world = World();
	Console console = Console();
	console.printWorld(world);
	system("pause");
}
