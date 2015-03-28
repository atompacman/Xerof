#include "MapGenerator.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                  GENERATION                                //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Map2*            MapGenerator::s_Map(NULL);
const MapConfig* MapGenerator::s_Config(NULL);

Map2& MapGenerator::generate(const MapConfig& i_Config)
{
    s_Map = new Map2(i_Config.m_Dim);
    s_Config = &i_Config;

	initWorldGeneratorSeed();
    fillWithOcean();
    placeInitialLandTiles();
    growLandmasses();
    
    return *s_Map;
}

void MapGenerator::fillWithOcean()
{
    // For progression bar
    UINT n(s_Map->area() / PGI);
    UINT progres(0);
    //
    for (UINT i = 0; i < s_Map->area(); ++i) {
        s_Map->m_Tiles[i] = new Tile();
        LOG_EVERY_N(n, DEBUG) << "World generation - Allocating tiles "
            << "to memory [" << std::setw(3) << ++progres * PGI << "%]";
    }
}

void MapGenerator::placeInitialLandTiles()
{
    UINT initTiles(s_Map->area() * s_Config->m_LandProp * s_Config->m_InitProp);

    for (EnvType envType : LAND_ENV_TYPES) {
        UINT envTiles(initTiles*s_Config->m_InitLandProp.proportionOf(envType));
        Constraint* constrs[] {
            new DistanceFromCenter(*s_Map, s_Config->m_LandDispertion),
            new EnvironmentIs(*s_Map, OCEAN)
        };
        generateEnv(envType, envTiles, constrs, 2, "Placing initial tiles");
    }
}

void MapGenerator::growLandmasses()
{
    UINT tiles(s_Map->area() * s_Config->m_LandProp * (1-s_Config->m_InitProp));

    for (EnvType envType : LAND_ENV_TYPES) {
        UINT envTiles(tiles * s_Config->m_LandTypeProp.proportionOf(envType));
        Constraint* constrs[] {
            new DistanceFromCenter(*s_Map, s_Config->m_LandDispertion),
            new Clustering(*s_Map, envType, s_Config->m_LandCompactness),
            new EnvironmentIs(*s_Map, OCEAN)
        };
        generateEnv(envType, envTiles, constrs, 2, "Growing landmasses");
    }
}

void MapGenerator::generateEnv(EnvType      i_Type,
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
		const Coord coord = randCoord();
		float totalProb(100.0);
        for (UINT i = 0; i < i_NumConstr; ++i) {
            totalProb *= i_Constr[i]->getWeightFor(coord);
		}
		if (nextRand(100) < totalProb) {
            UINT tileNum = coord.x + coord.y * MAP_DIMENSIONS.x;
            s_Map->m_Tiles[tileNum]->setEnvironment(i_Type);
	
            LOG_EVERY_N(n, DEBUG) << "World generation - " 
                << i_TaskDesc << " (" << ENV_NAMES[i_Type] 
                << ")[" << std::setw(3) << ++progres * PGI << "%]";
		}
	}

    // Delete constraints
    for (UINT i = 0; i < i_NumConstr; ++i) {
        delete i_Constr[i];
    }
}

const Coord MapGenerator::randCoord()
{
    UINT obw(s_Config->m_OceanBorderWidth);
    int x(nextRand(obw, s_Config->m_Dim.x - 2 * obw));
    int y(nextRand(obw, s_Config->m_Dim.y - 2 * obw));
    return Coord(x, y);
}