#include "CivController.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

CivController::CivController(const World& i_World) :
m_Civ(),
m_AI(new AtomAI()),
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

    addHuman(startLoc);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     ADD                                    //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void CivController::addHuman(Coord i_Pos)
{
    assert(m_Civ.m_People.size() < CIV_MAX_POP);
    assert(m_World.map().getTile(i_Pos).isPassable());
    m_Civ.m_People.emplace_back(Position(i_Pos));
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Civilization& CivController::getCiv() const
{
    return m_Civ;
}

Civilization& CivController::getCiv()
{
    return m_Civ;
}

AI* CivController::getAI() const
{
    return m_AI;
}