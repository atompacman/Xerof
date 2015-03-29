#pragma once
#include <assert.h>
#include "..\ai\AI.h"
#include "..\ai\AtomAI.h"
#include "Civilization.h"
#include "..\utils\Direction.h"
#include "..\utils\Elem2D.h"

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