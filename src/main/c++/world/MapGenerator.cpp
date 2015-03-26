#include "MapGenerator.h"

Map2* Constraint::s_Map;

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
	unsigned int progrIncr = 
        (int)(PROGRESSION_INCREMENTS_PERC * (float)area(MAP_DIMENSIONS));
	unsigned int countObjective = progrIncr;
	unsigned int currPerc = PROGRESSION_INCREMENTS_PERC;

	Coord coord;
	for (coord.y = 0; coord.y < MAP_DIMENSIONS.y; ++coord.y) {
		for (coord.x = 0; coord.x < MAP_DIMENSIONS.x; ++coord.x) {
			Tile* tile = new Tile();
			tile->setEnvironment(OCEAN);
			m_Tiles[linearize(coord)] = tile;

			++tileCount;
			if (tileCount > countObjective) {
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
		= area(MAP_DIMENSIONS) * LAND_PROPORTION_2 * INITIAL_LAND_TILES_2;
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
        area(MAP_DIMENSIONS) * LAND_PROPORTION_2 * (1 - INITIAL_LAND_TILES_2);
	Constraint* constrs[] = {
		new DistanceFromCenter(LAND_DISPERTION),
		new Clustering(GRASSLAND, LANDMASS_COMPACTNESS),
		new EnvironmentIs(OCEAN)
	};
	generateEnvironment(GRASSLAND, landTilesToPlace, 
        constrs, 3, "Growing landmasses");
}

void MapGenerator::generateEnvironment(EnvType      i_Type,
                                       UINT         i_NumElem,
                                       Constraint** i_Constr,
                                       int          i_NumConstr,
                                       const char*  i_TaskDesc)
{
	UINT elemPlaced = 0;
    UINT progrIncr = (int)(PROGRESSION_INCREMENTS_PERC*(float)i_NumElem);
    UINT countObjective = progrIncr;
    UINT currPerc = PROGRESSION_INCREMENTS_PERC;

    while (elemPlaced < i_NumElem) {
		Coord coord = randTile();
		float totalProb = 100.0;
        for (int i = 0; i < i_NumConstr; ++i) {
            totalProb *= i_Constr[i]->getWeightFor(coord);
		}
		if (nextRand(100) < totalProb) {
            m_Tiles[linearize(coord)]->setEnvironment(i_Type);
	
			++elemPlaced;
			if (elemPlaced > countObjective) {
                printProgress(i_TaskDesc, currPerc);
				countObjective += progrIncr;
				currPerc += PROGRESSION_INCREMENTS_PERC;
			}
		}
	}
}

void MapGenerator::printProgress(const char* i_TaskDesc, unsigned int i_Progress)
{
    LOG(DEBUG) << "World generation -:- " << std::setw(10)
        << i_TaskDesc << ": " << std::setw(3) << i_Progress << "%";
}
