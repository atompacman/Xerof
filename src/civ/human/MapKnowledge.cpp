#include "MapKnowledge.h"
#include <assert.h>
#include <bitset>
#include "Position.h"
#include "RangeOfSight.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

MapKnowledge::MapKnowledge(Dimensions i_MapDim) :
m_Tiles(new bool*[i_MapDim.y]),
m_MapDim(i_MapDim)
{
    for (unsigned int i = 0; i < i_MapDim.y; ++i) {
        m_Tiles[i] = new bool[i_MapDim.x];
        std::fill(m_Tiles[i], m_Tiles[i] + i_MapDim.x, false);
    }
}

MapKnowledge::~MapKnowledge()
{
    for (unsigned int i = 0; i < m_MapDim.y; ++i) {
        delete[] m_Tiles[i];
    }
    delete[] m_Tiles;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                 IS KNOWN                                   //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool MapKnowledge::isKnown(Coord i_Coord) const
{
    assert(i_Coord < m_MapDim);
    return m_Tiles[i_Coord.y][i_Coord.x];
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                DISCOVER                                    //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void MapKnowledge::discover(const Position&     i_Pos,
                            const RangeOfSight& i_ROS)
{
    assertNonCenterDir(i_Pos.facingDir());
    bool isDiag(isDiagonal(i_Pos.facingDir()));
    const RangeOfSight::ROSModel& rosModel(isDiag ? i_ROS.getDiagonalModel() :
                                                    i_ROS.getStraigthModel());
    switch (isDiag ? i_Pos.facingDir() - 4 : i_Pos.facingDir()) {
    case UP   : discoverUp   (i_Pos.tileCoord(), rosModel); break;
    case RIGHT: discoverRight(i_Pos.tileCoord(), rosModel); break;
    case DOWN : discoverDown (i_Pos.tileCoord(), rosModel); break;
    case LEFT : discoverLeft (i_Pos.tileCoord(), rosModel); break;
    }
}

void MapKnowledge::discoverUp(const Coord&                  i_Coord,
                              const RangeOfSight::ROSModel& i_ROSmodel)
{
    Coord map, ros;
    for (    map.y = i_Coord.y + i_ROSmodel.m_ULCorner.y,
             ros.y = 0; ros.y < i_ROSmodel.m_Dim.y; ++ros.y, ++map.y) {
        for (map.x = i_Coord.x + i_ROSmodel.m_ULCorner.x,
             ros.x = 0; ros.x < i_ROSmodel.m_Dim.x; ++ros.x, ++map.x) {
            if (map < m_MapDim) {
                m_Tiles[map.y][map.x] |= i_ROSmodel.m_Tiles[ros.y][ros.x];
            }
        }
    }
}

void MapKnowledge::discoverRight(const Coord&                  i_Coord,
                                 const RangeOfSight::ROSModel& i_ROSmodel)
{
    Coord map, ros;
    for (    map.x = i_Coord.x - i_ROSmodel.m_ULCorner.y,
             ros.y = 0; ros.y < i_ROSmodel.m_Dim.y; ++ros.y, --map.x) {
        for (map.y = i_Coord.y + i_ROSmodel.m_ULCorner.x,
             ros.x = 0; ros.x < i_ROSmodel.m_Dim.x; ++ros.x, ++map.y) {
            if (map < m_MapDim) {
                m_Tiles[map.y][map.x] |= i_ROSmodel.m_Tiles[ros.y][ros.x];
            }
        }
    }
}

void MapKnowledge::discoverDown(const Coord&                  i_Coord,
                                const RangeOfSight::ROSModel& i_ROSmodel)
{
    Coord map, ros;
    for (    map.y = i_Coord.y - i_ROSmodel.m_ULCorner.y,
             ros.y = 0; ros.y < i_ROSmodel.m_Dim.y; ++ros.y, --map.y) {
        for (map.x = i_Coord.x - i_ROSmodel.m_ULCorner.x,
             ros.x = 0; ros.x < i_ROSmodel.m_Dim.x; ++ros.x, --map.x) {
            if (map < m_MapDim) {
                m_Tiles[map.y][map.x] |= i_ROSmodel.m_Tiles[ros.y][ros.x];
            }
        }
    }
}

void MapKnowledge::discoverLeft(const Coord&                  i_Coord,
                                const RangeOfSight::ROSModel& i_ROSmodel)
{
    Coord map, ros;
    for (    map.x = i_Coord.x + i_ROSmodel.m_ULCorner.y,
             ros.y = 0; ros.y < i_ROSmodel.m_Dim.y; ++ros.y, ++map.x) {
        for (map.y = i_Coord.y - i_ROSmodel.m_ULCorner.x,
             ros.x = 0; ros.x < i_ROSmodel.m_Dim.x; ++ros.x, --map.y) {
            if (map < m_MapDim) {
                m_Tiles[map.y][map.x] |= i_ROSmodel.m_Tiles[ros.y][ros.x];
            }
        }
    }
}