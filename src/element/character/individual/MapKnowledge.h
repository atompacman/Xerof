#pragma once

#include <Elem2D.h>
#include <RangeOfSight.h>

/*============================================================================\\
| The list tiles a human knows about
|-----------------------------------------------------------------------------||
| Documentation is fun
\=============================================================================*/

struct Position;

enum class Visibility
{
    UNEXPLORED, FOG_OF_WAR, VISIBLE
};

class MapKnowledge : private Array2D<bool>
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    MapKnowledge(Dimensions i_MapDim);

    // GET VISIBILITY
    virtual Visibility getVisibility(Coord i_Coord) const;

    // DISCOVER
    void discover(const Position& i_Pos, const RangeOfSight& i_ROS);

private:
    SCoord              m_LastTile;
    Direction           m_LastDir;
    const RangeOfSight* m_LastROS;
};
