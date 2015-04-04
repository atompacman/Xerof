#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <assert.h>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "map\gen\MapGenerator.h"
/*============================================================================||
| The World !
|-----------------------------------------------------------------------------||
| For now, only contains the map. But later, will contain info about time,
| seasons...
\=============================================================================*/

class World
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    World();

    // GETTERS
    const Map& map() const;

private:
    Map m_Map;
};
