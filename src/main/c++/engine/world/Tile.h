#pragma once
#include "Background.h"
#include "Foreground.h"
#include "..\console\ConsoleColor.h"

class Tile
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	Tile();
	~Tile();

	// SETTERS
	void setForeground(Foreground*);
	void setBackground(Background*);

	// GETTERS
	const Foreground* getForeground() const;
	const Background* getBackground() const;

	// STATUS
	bool hasForeground() const;
	bool hasBackground() const;
	bool isPassable() const;

private:
	Foreground* front;
	Background* back;
};