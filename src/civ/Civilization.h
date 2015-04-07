#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <vector>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\Parameters.h"
#include "human\Human.h"
/*============================================================================||
| A group of humans
|-----------------------------------------------------------------------------||
| For now, a civ is not bigger than the sum of its parts...
\=============================================================================*/

class Civilization
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    Civilization(const Map& i_Map);

	// GETTERS
	const Human& getHuman(UINT i_ID) const;
    Human&       getHuman(UINT i_ID);

    // ADD
    void addHuman(Coord i_Pos);

	// STATUS
	UINT population() const;

private:
	std::vector<Human> m_People;

    const Map&         m_Map;
};