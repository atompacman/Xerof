#include "Map.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


Map::Map()
{

}


Map::~Map()
{

}

#include <iostream>
#include <windows.h> // WinApi header

using namespace std; // std::cout, std::cin

int main()
{
	HANDLE hConsole;
	int k;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// you can loop k higher to see more color choices
	for (k = 1; k < 256; k++)
	{
		// pick the colorattribute k you want
		SetConsoleTextAttribute(hConsole, k);
		cout << k << " I want to be nice today!" << endl;
	}

	cin.get(); // wait
	return 0;
}
