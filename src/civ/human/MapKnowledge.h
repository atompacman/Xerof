#pragma once

#include <Elem2D.h>
#include <RangeOfSight.h>

/*============================================================================\\
| The list tiles a human knows about
|-----------------------------------------------------------------------------||
| Documentation is fun
\=============================================================================*/

struct Position;

class MapKnowledge
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    MapKnowledge(Dimensions i_MapDim);
    ~MapKnowledge();

    // IS KNOWN
    virtual bool isKnown(Coord i_Coord) const;

    // DISCOVER
    void discover(const Position& i_Pos, const RangeOfSight& i_ROS);

private:
    bool**     m_Tiles;
    Dimensions m_MapDim;

    // DISCOVER
    void discoverUp   (const Coord&                  i_Coord,
                       const RangeOfSight::ROSModel& i_ROSmodel);
    void discoverRight(const Coord&                  i_Coord,
                       const RangeOfSight::ROSModel& i_ROSmodel);
    void discoverDown (const Coord&                  i_Coord,
                       const RangeOfSight::ROSModel& i_ROSmodel);
    void discoverLeft (const Coord&                  i_Coord,
                       const RangeOfSight::ROSModel& i_ROSmodel);
};