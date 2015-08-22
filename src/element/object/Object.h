#pragma once

#include <Direction.h>
#include <GraphicalElement.h>

/*============================================================================\\
| Base class of every animate object
|-----------------------------------------------------------------------------||
| Class hierarchy:
| GraphicalElement -> Object -> ...
\=============================================================================*/

enum class ObjSize
{
    // A quarter of a tile
    SMALL,
    // Half of a tile
    MEDIUM,
    // Whole tile
    BIG
};

class Object : public GraphicalElement
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Object(AssetID i_AssetID, ObjSize i_Size, bool i_IsPassable) :
        GraphicalElement(i_AssetID),
        m_Size(i_Size),
        m_Disposition(),
        m_IsPassable(i_IsPassable)
    {}

    // GETTERS
    ObjSize     getSize()        const { return m_Size; }
    Disposition getDisposition() const { return m_Disposition; }

    // STATUS
    bool        isPassable()     const { return m_IsPassable; }

private:
    ObjSize     m_Size;
    Disposition m_Disposition;
    bool        m_IsPassable;
};
