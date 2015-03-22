#include "World.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

World::World()
{
	LOG(INFO) << "World generation -:- Generating world";
	map = new Map();
}