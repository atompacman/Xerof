#include "MapGenerator.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                  GENERATION                                //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void MapGenerator::generate(Map2& o_Map, const MapConfig& i_Config)
{
	initWorldGeneratorSeed();
    fillWithOcean(o_Map);
    placeInitialLandTiles(o_Map);
    growLandmasses(o_Map);
}

void MapGenerator::fillWithOcean(Map2& io_Map)
{
    UINT numTiles(area(MAP_DIMENSIONS));

    // For progression bar
    UINT n(numTiles / PGI);
    UINT progres(0);
    //
    for (UINT i(0); i < numTiles; ++i) {
        io_Map.m_Tiles[i] = new Tile();
        LOG_EVERY_N(n, DEBUG) << "World generation - Allocating tiles "
            << "to memory [" << std::setw(3) << ++progres * PGI << "%]";
    }
}

void MapGenerator::placeInitialLandTiles(Map2& io_Map)
{
    UINT initLandProportion(LAND_PROPORTION_2 * INITIAL_LAND_TILES_2);
    UINT initLand2Place(area(MAP_DIMENSIONS) * initLandProportion);
	Constraint* constrs[] {
        new DistanceFromCenter(io_Map, LAND_DISPERTION),
        new EnvironmentIs(io_Map, OCEAN)
	};
    generateEnvironment(io_Map, GRASSLAND, initLand2Place,
		constrs, 2, "Placing initial land tiles");
}

void MapGenerator::growLandmasses(Map2& io_Map)
{
    UINT normalLandProportion(LAND_PROPORTION_2 * (1 - INITIAL_LAND_TILES_2));
    UINT land2Place(area(MAP_DIMENSIONS) * normalLandProportion);
	Constraint* constrs[] {
        new DistanceFromCenter(io_Map, LAND_DISPERTION),
        new Clustering(io_Map, GRASSLAND, LANDMASS_COMPACTNESS),
        new EnvironmentIs(io_Map, OCEAN)
	};
    generateEnvironment(io_Map, GRASSLAND, land2Place,
        constrs, 3, "Growing landmasses");
}

void MapGenerator::generateEnvironment(Map2&        io_Map, 
                                       EnvType      i_Type,
                                       UINT         i_NumElem,
                                       Constraint** i_Constr,
                                       UINT         i_NumConstr,
                                       const char*  i_TaskDesc)
{
    // For progression bar
    UINT n = i_NumElem / PGI;
    UINT progres(0);
    //
    UINT elemPlaced(0);
    
    while (elemPlaced < i_NumElem) {
		Coord coord = randTile();
		float totalProb(100.0);
        for (UINT i = 0; i < i_NumConstr; ++i) {
            totalProb *= i_Constr[i]->getWeightFor(coord);
		}
		if (nextRand(100) < totalProb) {
            io_Map.m_Tiles[coord.x + coord.y * MAP_DIMENSIONS.x]->setEnvironment(i_Type);
	
            LOG_EVERY_N(n, DEBUG) << "World generation - " << i_TaskDesc
                << " [" << std::setw(3) << ++progres * PGI << "%]";
		}
	}
}

Coord MapGenerator::randTile()
{
    int x(nextRand(OCEAN_MARGINS, MAP_DIMENSIONS.x - 2 * OCEAN_MARGINS));
    int y(nextRand(OCEAN_MARGINS, MAP_DIMENSIONS.y - 2 * OCEAN_MARGINS));
    return Coord(x, y);
}