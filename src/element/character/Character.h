#pragma once

#include <GraphicalElement.h>
#include <Position.h>

/*============================================================================\\
| Base class of every animate character of the game
|-----------------------------------------------------------------------------||
| Class hierarchy:
| GraphicalElement -> Character -> ...
\=============================================================================*/

class Character : public GraphicalElement
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Character(AssetID i_AssetID, Position i_Pos) :
        GraphicalElement(i_AssetID),
        m_Pos(i_Pos)
    {}

    // GETTERS
    const Position& getPosition() const { return m_Pos; }
    Position&       getPosition()       { return m_Pos; }

protected:
    Position m_Pos;
};