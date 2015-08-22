#pragma once

#include <Object.h>

/*============================================================================\\
| Large plant objects
|-----------------------------------------------------------------------------||
| Class hierarchy:
| GraphicalElement -> Object -> LargePlant -> ...
|
|   - Occupies a whole tile
|   - Not passable
\=============================================================================*/

class LargePlant : public Object
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    LargePlant(AssetID i_AssetID) :
        Object(i_AssetID, ObjSize::BIG, false)
    {}
};
