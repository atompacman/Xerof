#include <Individual.h>
#include <Map.h>
#include <MathUtils.h>
#include <MoveProcess.h>
#include <Parameters.h>
#include <Tile.h>

const double MoveProcess::s_DELTA = 0.5 / TARGET_FPS;

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

MoveProcess::MoveProcess(Individual&     i_Indiv,
                         const Position& i_Dest,
                         Map&            i_Map) :
    m_Individual(i_Indiv),
    m_InitTile(i_Indiv.getPosition().tileCoord()),
    m_DestTile(i_Dest.tileCoord()),
    m_Delta((i_Dest.coord() - i_Indiv.getPosition().coord()) / TARGET_FPS),
    m_Map(i_Map)
{
    // Turn head in the direction told by destination
    m_Individual.getPosition().setDir(i_Dest.facingDir());

    // Explore the map in this new direction
    m_Individual.discoverSurroundingTiles();
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                               NEXT ITERATION                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void MoveProcess::nextIter()
{
    // Get current position
    Position& pos(m_Individual.getPosition());
    DCoord roundPos(roundCoord(pos.coord()));

    // Move in facing direction
    pos.moveForward(m_Delta);
    bool changedTile(false);

    // If character is changing tile in the x axis
    if (abs(roundPos.x - pos.coord().x) < s_DELTA) {
        // Moving right
        if (m_DestTile.x > m_InitTile.x) {
            // Set human position right on the edge of the new tile
            pos.setX(roundPos.x);
        }
        // Moving left
        else {
            // Set human position right before the new tile
            pos.setX(roundPos.x - EPSILON);
        }
        changedTile = true;
    }

    // If character is changing tile in the y axis
    if (abs(roundPos.y - pos.coord().y) < s_DELTA) {
        // Moving down
        if (m_DestTile.y > m_InitTile.y) {
            // Set human position right on the edge of the new tile
            pos.setY(roundPos.y);
        }
        // Moving up
        else {
            // Set human position right before the new tile
            pos.setY(roundPos.y - EPSILON);
        }
        changedTile = true;
    }

    // If character steps in destination tile
    if (changedTile) {
        // Remove human from previous tile
        m_Map(m_InitTile).setIndividual(NULL);

        // Set human on new tile
        m_Map(m_DestTile).setIndividual(&m_Individual);

        // (Potentially) discover tiles around its new position
        m_Individual.discoverSurroundingTiles();
    }
}