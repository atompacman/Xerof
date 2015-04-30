#include "MoveProcess.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const double MoveProcess::s_DELTA = 0.5 / TARGET_FPS;

MoveProcess::MoveProcess(HumanInfo&      i_Human,
                         const Position& i_Dest, 
                         Map&            i_Map):
m_Human(i_Human),
m_InitTile(i_Human.getPos().tileCoord()),
m_DestTile(i_Dest.tileCoord()),
m_Delta((i_Dest.coord() - i_Human.getPos().coord()) / TARGET_FPS),
m_Map(i_Map)
{
    // Turn head in the direction told by destination
    m_Human.getPos().setDir(i_Dest.facingDir());

    // Explore the map in this new direction
    m_Human.discoverSurroundingTiles();
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                               NEXT ITERATION                               //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void MoveProcess::nextIter()
{
    // Get current position
    Position& pos(m_Human.getPos());
    DCoord roundPos(roundCoord(pos.coord()));

    // Move in facing direction
    pos.moveForward(m_Delta);
    bool changedTile(false);

    // If character is changing tile in the x axis
    if (abs(pos.coord().x - roundPos.x) < s_DELTA) {
        // Set human position right on the edge of the tile
        pos.setX(roundPos.x);
        changedTile = true;
    }

    // If character is changing tile in the y axis
    if (abs(pos.coord().y - roundPos.y) < s_DELTA) {
        // Set human position right on the edge of the tile
        pos.setY(roundPos.y);
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