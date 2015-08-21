#pragma once

#include <MapElement.h>

/*============================================================================\\
| Interface for objects
|-----------------------------------------------------------------------------||
| Nothing special for now!
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

class Object : public MapElement
{
public:
    // GETTERS
    virtual ObjSize getSize() const = 0;

    // STATUS
    virtual bool isPassable() const = 0;
};
