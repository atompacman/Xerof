#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <vector>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "human\HumanInfo.h"
#include "..\world\map\Map.h"
#include "..\Parameters.h"
/*============================================================================||
| A group of humans
|-----------------------------------------------------------------------------||
| For now, a civ is not bigger than the sum of its parts...
\=============================================================================*/

class Civilization
{
    friend class CivController;

public:
	// CONSTRUCTOR/DESTRUCTOR
    Civilization();

	// GETTERS
	const HumanInfo& getHuman(unsigned int i_ID) const;
    HumanInfo&       getHuman(unsigned int i_ID);

	// STATUS
	unsigned int population() const;

private:
	std::vector<HumanInfo> m_People;
};