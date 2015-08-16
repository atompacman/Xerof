#pragma once

#include <MapKnowledge.h>

/*============================================================================\\
| Used by the GameLoop to tell the Display to show a tiles
|-----------------------------------------------------------------------------||
| Documentation is fun
\=============================================================================*/

class FullMapKnowledge : public MapKnowledge
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    FullMapKnowledge() :
        MapKnowledge(Dimensions(0,0))
    {}

    // IS KNOWN
    bool isKnown(Coord i_Coord) const
    {
        return true;
    }
};