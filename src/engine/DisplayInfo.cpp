#include <DisplayInfo.h>
#include <Individual.h>
#include <Map.h>
#include <Tile.h>

FullMapKnowledge DisplayInfo::s_FullMapKnow = FullMapKnowledge();

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

DisplayInfo::DisplayInfo(Map& i_Map, Individual* i_SelectedIndiv) :
m_Camera(i_Map.dimensions()),
m_SelectedHuman(i_SelectedIndiv),
m_FollowSelection(false),
m_Map(i_Map),
m_MapKnow(NULL)
{
    // Select initial human
    i_SelectedIndiv->select();

    // Zoom on initial selected human
    m_Camera.setPosition(m_SelectedHuman->getPosition().coord());
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Camera& DisplayInfo::getCamera() const
{
    return m_Camera;
}

Camera& DisplayInfo::getCamera()
{
    return m_Camera;
}

const Map& DisplayInfo::getMap() const
{
    return m_Map;
}

Map& DisplayInfo::getMap()
{
    return m_Map;
}

const Individual* DisplayInfo::getSelectedChar() const
{
    return m_SelectedHuman;
}

bool DisplayInfo::doFollowSelection() const
{
    return m_FollowSelection;
}

const MapKnowledge&	DisplayInfo::getMapKnowledge() const
{
    return m_SelectedHuman == NULL ? s_FullMapKnow :
                                     m_SelectedHuman->getMapKnowledge();
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   SETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void DisplayInfo::clearSelection()
{
    if (m_SelectedHuman != NULL) {
        m_SelectedHuman->unselect();
        m_SelectedHuman = NULL;
        m_FollowSelection = false;
    }
}

void DisplayInfo::setSelection(Coord i_SelectTile)
{
    // If clicked tile is out of the map, clear selection
    if (!(i_SelectTile < m_Map.dimensions())) {
        clearSelection();
        return;
    }

    // Get selected human
    Individual* currSelect(m_Map(i_SelectTile).getIndividual());

    // If there is no human on selected tile
    if (currSelect == NULL) {
        clearSelection();
        return;
    }

    // If selection didn't change
    if (currSelect == m_SelectedHuman) {
        clearSelection();
        return;
    }

    // Do the actual selection
    clearSelection();
    m_SelectedHuman = currSelect;
    m_SelectedHuman->select();
}

void DisplayInfo::switchFollowSelection()
{
    m_FollowSelection = !m_FollowSelection;
}

void DisplayInfo::updateCameraPosition()
{
    // Center camera on selection
    if (m_SelectedHuman != NULL && m_FollowSelection) {
        m_Camera.setPosition(m_SelectedHuman->getPosition().coord());
    }
}