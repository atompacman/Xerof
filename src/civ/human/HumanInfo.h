#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\..\engine\Assets.h"
#include "Position.h"
#include "..\..\world\map\tile\MapElement.h"
/*============================================================================||
| Data related to a single human entity
|-----------------------------------------------------------------------------||
| Is basically a data container
\=============================================================================*/

class HumanInfo : public MapElement
{
    friend class HumanPerception;

public:
	// CONSTRUCTOR/DESTRUCTOR
    HumanInfo(const Position& i_StartingPos);

	// GETTERS
    const Position& getPos() const;
    Position&       getPos();

    // SETTERS
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
    Position m_Pos;
	bool     m_IsReady;
	float    m_MoveSpeed;
	UINT     m_ROSight;
};