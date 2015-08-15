#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\..\engine\Assets.h"
#include "..\..\world\map\tile\MapElement.h"
#include "MapKnowledge.h"
#include "Position.h"
#include "RangeOfSight.h"
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
    HumanInfo(const Position& i_StartingPos, Dimensions i_MapDim);

    // GETTERS
    const Position&     getPosition() const;
    Position&           getPosition();
    const MapKnowledge& getMapKnowledge() const;

    // SETTERS
    void setReady();
    void setBusy();
    void select();
    void unselect();

    // STATE
    bool isReady() const;
    bool isSelected() const;

    // DISCOVER SURROUNDING TILES
    void discoverSurroundingTiles();

    // STATS
    float getMoveSpeed() const;

    // ASSET
    virtual AssetID assetFile() const { return CHARACTER; }

private:
    Position      m_Pos;
    bool          m_IsReady;
    bool          m_IsSelected;
    float         m_MoveSpeed;
    RangeOfSight* m_ROS;
    MapKnowledge  m_MapKnow;
};