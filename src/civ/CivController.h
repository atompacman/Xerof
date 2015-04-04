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
    CivController(const World& i_World);
    ~CivController();

	// DAWN OF CIVILIZATION
	void placeFirstHuman();

	// GETTERS
    const Civilization& getCiv() const;
    AI*                 getAI() const;
    Human&              getHuman(UINT i_ID);

private:
    Civilization m_Civ;
    AI*          m_AI;

    const World& m_World;
};