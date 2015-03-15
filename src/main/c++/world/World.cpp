#include "World.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

World::World()
{
	if (DEBUG_MODE && VERBOSE >= 3) {
		fprintf(stdout, "World generation -:- Generating world\n");
	}
	map = new Map();
}