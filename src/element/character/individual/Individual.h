#pragma once

#include <Assets.h>
#include <Character.h>
#include <Elem2D.h>
#include <MapKnowledge.h>
#include <Position.h>
#include <RangeOfSight.h>

/*============================================================================\\
| Data related to a single human entity
|-----------------------------------------------------------------------------||
| Class hierarchy:
| GraphicalElement -> Character -> Individual
|
| Is basically a data container
\=============================================================================*/

class Individual : public Character
{
    friend class WorldPerception;

public:
    // CONSTRUCTOR/DESTRUCTOR
    Individual(const Position&     i_StartingPos,
               Dimensions          i_MapDim,
               const RangeOfSight& i_ROS) :
        Character(CHARACTER, i_StartingPos),
        m_IsReady(true),
        m_IsSelected(false),
        m_MoveSpeed(1.0),
        m_ROS(i_ROS),
        m_MapKnow(i_MapDim)
    {
        discoverSurroundingTiles();
    }

    // GETTERS
    const MapKnowledge& getMapKnowledge() const { return m_MapKnow; }

    // SETTERS
    void setReady() { m_IsReady = true; }
    void setBusy()  { m_IsReady = false; }
    void select()   { m_IsSelected = true; }
    void unselect() { m_IsSelected = false; }

    // STATE
    bool isReady()    const { return m_IsReady; }
    bool isSelected() const { return m_IsSelected; }

    // DISCOVER SURROUNDING TILES
    void discoverSurroundingTiles() { m_MapKnow.discover(m_Pos, m_ROS); }

    // STATS
    double getMoveSpeed() const { return m_MoveSpeed; }

private:
    bool                m_IsReady;
    bool                m_IsSelected;
    double              m_MoveSpeed;
    const RangeOfSight& m_ROS;
    MapKnowledge        m_MapKnow;
};
