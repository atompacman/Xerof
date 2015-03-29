#include "CivController.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

CivController::CivController(const World& i_World) :
m_Civ(i_World.map()),
m_AI(new AtomAI(m_Civ)),
m_World(i_World)
{}

CivController::~CivController()
{
    delete m_AI;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                            DAWN OF CIVILIZATION                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void CivController::placeFirstHuman()
{
	Coord startLoc;
	do {
        startLoc = m_World.map().randCoord();
    } while (!m_World.map().getTile(startLoc).isPassable());

    m_Civ.addHuman(startLoc);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Civilization& CivController::getCiv() const
{
    return m_Civ;
}

AI* CivController::getAI() const
{
    return m_AI;
}

Human& CivController::getHuman(UINT i_ID)
{
    return m_Civ.getHuman(i_ID);
}