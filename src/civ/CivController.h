#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <assert.h>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "ai\AtomAI.h"
#include "Civilization.h"
#include "..\world\World.h"
/*============================================================================||
| Manages a civilization
|-----------------------------------------------------------------------------||
| Supervises civilization initialization and the AI
\=============================================================================*/

class CivController
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    CivController(World& i_World);
    ~CivController();

	// DAWN OF CIVILIZATION
	void placeFirstHuman();

    // ADD
    void addHuman(Coord i_Pos);

	// GETTERS
    const Civilization& getCiv() const;
    Civilization&       getCiv();
    AI*                 getAI() const;

private:
    Civilization m_Civ;
    AI*          m_AI;

    World& m_World;
};