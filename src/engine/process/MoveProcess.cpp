#include "MoveProcess.h"
#include "..\..\civ\human\HumanInfo.h"
#include "..\..\world\map\Map.h"
#include "..\..\utils\MathUtils.h"
#include "..\..\Parameters.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const double MoveProcess::s_DELTA = 0.5 / TARGET_FPS;

MoveProcess::MoveProcess(HumanInfo&      i_Human,
                         const Position& i_Dest,
                         Map&            i_Map) :
    m_Human(i_Human),
    m_InitTile(i_Human.getPosition().tileCoord()),
    m_DestTile(i_Dest.tileCoord()),
    m_Delta((i_Dest.coord() - i_Human.getPosition().coord()) / TARGET_FPS),
    m_Map(i_Map)
{
    // Turn head in the direction told by destination
    m_Human.getPosition().setDir(i_Dest.facingDir());

    // Explore the map in this new direction
    m_Human.discoverSurroundingTiles();
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                               NEXT ITERATION                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void MoveProcess::nextIter()
{
    // Get current position
    Position& pos(m_Human.getPosition());
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
        m_Map.getTile(m_InitTile).setHuman(NULL);

        // Set human on new tile
        m_Map.getTile(m_DestTile).setHuman(&m_Human);

        // (Potentially) discover tiles around its new position
        m_Human.discoverSurroundingTiles();
    }
}