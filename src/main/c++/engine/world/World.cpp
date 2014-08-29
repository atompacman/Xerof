#include "World.h"


World::World() {

}

World::~World() {

}

//===================================INCLUDES==================================
#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;


//=============================FUNCTION PROTOTYPES=============================
unsigned char GetColorCode(unsigned char colorBackground,
	unsigned char colorForeground);


//==================================MAIN ENTRY=================================
int main(void)
{
	//handle to console window's context
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	unsigned char colorBackground = 0x00; //background color code
	unsigned char colorForeground = 0x00;//foreground color code
	unsigned char colorCode = 0x00; //high:background, low:foreground


	//---------------OUTPUT COLORFUL LITERAL---------------
	//set text color (0x08 = black background, grey foreground)
	SetConsoleTextAttribute(hConsole, 0x08);
	cout << "I don't always like ";

	//set text color (0x0E = black background, yellow foreground)
	SetConsoleTextAttribute(hConsole, 0x0E);
	cout << "Cake";

	//set text color (0x08 = black background, grey foreground)
	SetConsoleTextAttribute(hConsole, 0x08);
	cout << ", but when I do it's always a ";

	//set text color (0xC0 = red background, black foreground)
	SetConsoleTextAttribute(hConsole, 0xC0);
	cout << "Lie!" << endl << endl << endl;



	//------------------OUTPUT COLOR CHART-----------------
	//output hexidecimal notation
	cout << setbase(16);

	//loop through each background color (0 to 15 = 16 possible colors)
	for (colorBackground = 0; colorBackground < 16; colorBackground++)
	{

		//loop through each foreground color (0 to 15 = 16 possible colors)
		for (colorForeground = 0; colorForeground < 16; colorForeground++)
		{

			//get color code as one variable
			colorCode = GetColorCode(colorBackground, colorForeground);

			//set front and back colors
			SetConsoleTextAttribute(hConsole, colorCode);

			//output the color code
			cout << setfill('0')                 //set fill character
				<< setw(2)                      //create width for numbers
				<< uppercase                    //set output to uppercase
				<< static_cast<int>(colorCode)  //print colorCode as hex
				<< ' ';                         //padding for next value
		}

		//start new line for next background color
		cout << '\n';
	}
	system("pause");
	return (0);
}


//=============================FUNCTION DEFINITIONS============================
unsigned char GetColorCode(unsigned char colorBackground,
	unsigned char colorForeground)
{
	//return most signifigant bit of colorBackground and
	//least signifigant bit of colorForground as one byte
	return (colorBackground << 4) + colorForeground;
}
