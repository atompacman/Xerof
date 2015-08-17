#include <assert.h>
#include <AtomAI.h>
#include <CivController.h>
#include <Parameters.h>
#include <Position.h>
#include <Tile.h>
#include <World.h>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

CivController::CivController(World& i_World) :
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
        startLoc = m_World.map().getRandomCoord();
    } while (!m_World.map()(startLoc).isPassable());

    addHuman(startLoc);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     ADD                                    //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void CivController::addHuman(Coord i_Pos)
{
    // Assert max pop is not reached
    assert(m_Civ.m_People.size() < CIV_MAX_POP);

    // Get tile where human will be
    Tile& tile(m_World.map()(i_Pos));

    // Assert it is human-passable
    assert(tile.isPassable());

    // Add it to the civ
    m_Civ.m_People.emplace_back(Position(i_Pos), m_World.map().dimensions());

    // Add a reference in the map
    tile.setHuman(&m_Civ.m_People.back());
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