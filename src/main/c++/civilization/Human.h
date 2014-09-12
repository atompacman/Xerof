#pragma once
#include "..\world\World.h"

class Human: public MapElement
{
public:
	Position position;

	// CONSTRUCTOR/DESCTRUCTOR
	Human(Position);

	// SETTERS
	void setReady();
	void setBusy();

	// GETTERS
	const Tile*** const getSurroundingTiles() const;
	const Tile* const getTileInFront() const;
	EnvType getEnvironnementInFront() const;
	bool isReady() const;

	// STATS
	float getMoveSpeed() const;
	unsigned int getRangeOfSight() const;

	// ASSET
	virtual Asset assetFile() const { return APARATUS3; }

private:
	bool ready;
	float moveSpeed;
	unsigned int rangeOfSight;
};