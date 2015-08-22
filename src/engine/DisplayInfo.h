#pragma once

#include <Camera.h>
#include <FullMapKnowledge.h>

/*============================================================================\\
| Data that is passed to the Display class "draw" method
|-----------------------------------------------------------------------------||
| - Camera
| - Character selection
| - Map
\=============================================================================*/

class Individual;
class Map;

class DisplayInfo
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    DisplayInfo(Map& i_Map, Individual* i_SelectedIndiv);

    // GETTERS
    const Camera&       getCamera() const;
    Camera&             getCamera();
    const Map&          getMap() const;
    Map&                getMap();
    const Individual*    getSelectedChar() const;
    bool                doFollowSelection() const;
    const MapKnowledge& getMapKnowledge() const;

    // SETTERS
    void clearSelection();
    void setSelection(Coord i_SelectTile);
    void switchFollowSelection();
    void updateCameraPosition();

private:
    // Camera
    Camera m_Camera;

    // Selected human
    Individual* m_SelectedHuman;

    // If camera follows selected human
    bool m_FollowSelection;

    // Map
    Map& m_Map;

    // Visible/shadowed/unexplored tiles
    const MapKnowledge* m_MapKnow;

    // Default map knowledge (all map is visible)
    static FullMapKnowledge s_FullMapKnow;
};