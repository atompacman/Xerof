#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "HumanInfo.h"
#include "..\..\world\map\Map.h"
/*============================================================================||
| The perception of the world from the perspective of a human
|-----------------------------------------------------------------------------||
| Used by AIs
\=============================================================================*/

class HumanPerception
{
public:
    // CONSTRUCTOR/DESTRUCTOR 
    HumanPerception(const HumanInfo& i_Info, const Map& i_Map);

    // GETTERS
    const Position& getPosition() const;

    // SURROUNDINGS
    bool        isWithinMapLimits(Direction i_Dir) const;
    const Tile& getTileInDir(Direction i_Dir) const;
    const Tile& getTileInFront() const;
    Biome       getBiomeInFront() const;

private:
    const HumanInfo& m_Info;
    const Map&       m_Map;
};