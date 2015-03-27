#include "World.h"

World* World::s_World;

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

World::World()
{
	LOG(INFO) << "World generation -:- Generating world";
	m_Map = new Map();
}