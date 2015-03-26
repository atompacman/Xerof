#pragma once
#include "..\utils\Elem2D.h"
#include "..\world\World.h"

class Human: public MapElement
{
public:
	Position m_Pos;

	// CONSTRUCTOR/DESTRUCTOR
    Human(Position i_Pos);

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
	bool  m_IsReady;
	float m_MoveSpeed;
	UINT  m_ROSight;
};