#pragma once
#include <stdlib.h>
#include "..\utils\Elem2D.h"
#include "..\world\World.h"

class Human : public MapElement
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    Human(const Position& i_StartingPos, const Map& i_Map);

	// GETTERS
    const Position& getPos() const;
    Position&       getPos();

    // SURROUNDINGS
    const Tile*** const getSurroundingTiles() const;
    const Tile&         getTileInDir(Direction i_Dir) const;
    const Tile&         getTileInFront() const;
    EnvType             getEnvInFront() const;

    // SETTERS
    void setDir(Direction i_Dir);
    void setReady();
    void setBusy();

    // STATE
    bool isReady() const;

	// STATS
	float getMoveSpeed() const;
	UINT  getRangeOfSight() const;

	// ASSET
	virtual AssetID assetFile() const { return APARATUS3; }

private:
    Position    m_Pos;
	bool        m_IsReady;
	float       m_MoveSpeed;
	UINT        m_ROSight;

    const Map&  m_Map;
};