#include "DisplayInfo.h"

FullMapKnowledge DisplayInfo::s_FullMapKnow = FullMapKnowledge();

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

DisplayInfo::DisplayInfo(Map& i_Map, HumanInfo* i_SelectedHuman) :
m_Camera(i_Map.dim()),
m_SelectedHuman(i_SelectedHuman),
m_FollowSelection(false),
m_Map(i_Map),
m_MapKnow(NULL)
{
	// Select initial human
	i_SelectedHuman->select();

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

const HumanInfo* DisplayInfo::getSelectedChar() const
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
	if (!(i_SelectTile < m_Map.dim())) {
		clearSelection();
		return;
	}

	// Get selected human
	HumanInfo* currSelect(m_Map.getTile(i_SelectTile).getHuman());

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