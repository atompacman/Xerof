#include <assert.h>
#include <bitset>
#include <MapKnowledge.h>
#include <Position.h>
#include <RangeOfSight.h>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

MapKnowledge::MapKnowledge(Dimensions i_MapDim) :
Array2D<bool>(i_MapDim),
m_LastTile(),
m_LastDir(),
m_LastROS(NULL)
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                 IS KNOWN                                   //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Visibility MapKnowledge::getVisibility(Coord i_Coord) const
{
    assert(i_Coord < m_Dim);

    // If tile was never explored
    if (!operator()(i_Coord)) {
        return Visibility::UNEXPLORED;
    }

    // If tile is visible
    if (m_LastROS->isVisible(toSCoord(i_Coord) - m_LastTile, m_LastDir)) {
        return Visibility::VISIBLE;
    }

    return Visibility::FOG_OF_WAR;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                DISCOVER                                    //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void MapKnowledge::discover(const Position& i_Pos, const RangeOfSight& i_ROS)
{
    m_LastTile = toSCoord(i_Pos.tileCoord());
    m_LastDir = i_Pos.facingDir();
    m_LastROS = &i_ROS;
    SCoord ulCorner(i_ROS.getWindowULCorner(m_LastDir));
    SCoord lrCorner(i_ROS.getWindowLRCorner(m_LastDir));

    SCoord centered;
    for (    centered.y = ulCorner.y; centered.y < lrCorner.y; ++centered.y) {
        for (centered.x = ulCorner.x; centered.x < lrCorner.x; ++centered.x) {
            Coord onMap(toCoord(m_LastTile + centered));
            if (!(onMap < m_Dim)) {
                continue;
            }
            std::vector<bool>::reference curr(operator()(onMap));
            curr = curr || i_ROS.isVisible(centered, m_LastDir);
        }
    }
}
