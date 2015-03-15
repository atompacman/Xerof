#include "MapGenerator.h"

Map2* Constraint::map;

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

MapGenerator::MapGenerator()
{
	Constraint::setMap(this);
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                  GENERATION                 //
//- - - - - - - - - - - - - - - - - - - - - - -//

Map2* MapGenerator::generate()
{
	initWorldGeneratorSeed();
	fillWithOcean();
	placeInitialLandTiles();
	growLandmasses();
	return this;
}

void MapGenerator::fillWithOcean()
{
	unsigned int tileCount = 0;
	unsigned int progrIncr 
		= (int)(PROGRESSION_INCREMENTS_PERC * (float)MAP_DIMENSIONS.area());
	unsigned int countObjective = progrIncr;
	unsigned int currPerc = PROGRESSION_INCREMENTS_PERC;

	Coord<int> coord = Coord<int>();
	for (coord.y = 0; coord.y < MAP_DIMENSIONS.y; ++coord.y) {
		for (coord.x = 0; coord.x < MAP_DIMENSIONS.x; ++coord.x) {
			Tile* tile = new Tile();
			tile->setEnvironment(OCEAN);
			tiles[linearize(coord)] = tile;

			++tileCount;
			if (DEBUG_MODE && VERBOSE >= 2 && tileCount > countObjective) {
				printProgress("Allocating tiles to memory", currPerc);
				countObjective += progrIncr;
				currPerc += PROGRESSION_INCREMENTS_PERC;
			}
		}
	}
}

void MapGenerator::placeInitialLandTiles()
{
	unsigned int initialLandTilesToPlace
		= MAP_DIMENSIONS.area() * LAND_PROPORTION_2 * INITIAL_LAND_TILES_2;
	Constraint* constrs[] = {
		new DistanceFromCenter(LAND_DISPERTION), 
		new EnvironmentIs(OCEAN)
	};
	generateEnvironment(GRASSLAND, initialLandTilesToPlace, 
		constrs, 2, "Placing initial land tiles");
}

void MapGenerator::growLandmasses()
{
	unsigned int landTilesToPlace = 
		MAP_DIMENSIONS.area() * LAND_PROPORTION_2 * (1 - INITIAL_LAND_TILES_2);
	Constraint* constrs[] = {
		new DistanceFromCenter(LAND_DISPERTION),
		new Clustering(GRASSLAND, LANDMASS_COMPACTNESS),
		new EnvironmentIs(OCEAN)
	};
	generateEnvironment(GRASSLAND, landTilesToPlace,
		constrs, 3, "Growing landmasses");
}

void MapGenerator::generateEnvironment(EnvType type, unsigned int elemQuant,
	Constraint** constraints, int nbConst, const char* taskDesc)
{
	unsigned int elemPlaced = 0;
	unsigned int progrIncr = (int)(PROGRESSION_INCREMENTS_PERC * (float)elemQuant);
	unsigned int countObjective = progrIncr;
	unsigned int currPerc = PROGRESSION_INCREMENTS_PERC;

	while (elemPlaced < elemQuant) {
		Coord<int> coord = randTile();
		float totalProb = 100.0;
		for (int i = 0; i < nbConst; ++i) {
			totalProb *= constraints[i]->getWeightFor(coord);
		}
		if (nextRand(100) < totalProb) {
			tiles[linearize(coord)]->setEnvironment(type);
	
			++elemPlaced;
			if (DEBUG_MODE && VERBOSE >= 2 && elemPlaced > countObjective) {
				printProgress(taskDesc, currPerc);
				countObjective += progrIncr;
				currPerc += PROGRESSION_INCREMENTS_PERC;
			}
		}
	}
}

void MapGenerator::printProgress(const char* taskDesc, unsigned int progress)
{
	fprintf(stdout, "World generation -:- %s: %3d%%\n", taskDesc, progress);
}
