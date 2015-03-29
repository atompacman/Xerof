#include "MapGenerator.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                  GENERATION                                //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Map*             MapGenerator::s_Map(NULL);
const MapConfig* MapGenerator::s_Config(NULL);

Map& MapGenerator::generate(const MapConfig& i_Config)
{
    s_Map = new Map(i_Config.m_Dim);
    s_Config = &i_Config;

    placeInitialLandTiles();
    growLandmasses();
    
    return *s_Map;
}

void MapGenerator::placeInitialLandTiles()
{
    // Compute how many initial tiles to place
    UINT initTiles(s_Map->area() * s_Config->m_LandProp * s_Config->m_InitProp);

    // Set constrains that are common for all env. type
    Constrs constrs(2);
    constrs[0] = new DistanceFromCenter(*s_Map, s_Config->m_LandDispertion);
    constrs[1] = new EnvironmentIs(*s_Map, OCEAN);

    for (EnvType envType : LAND_ENV_TYPES) {
        // Compute how many initial tiles to place for specific env. type
        UINT envTiles(initTiles*s_Config->m_InitLandProp.proportionOf(envType));

        // Generate tiles for specific env. type
        generateEnv(envType, envTiles, constrs, "Placing initial tiles");
    }

    // Delete constraints that are common for all env. type
    delete constrs[0];
    delete constrs[1];
}

void MapGenerator::growLandmasses()
{
    // Compute how many tiles to place
    UINT tiles(s_Map->area() * s_Config->m_LandProp * (1-s_Config->m_InitProp));

    // Set constrains that are common for all env. type
    Constrs constrs(3);
    constrs[0] = new DistanceFromCenter(*s_Map, s_Config->m_LandDispertion);
    constrs[1] = new EnvironmentIs(*s_Map, OCEAN);

    // Generate tiles for each env. type
    for (EnvType envType : LAND_ENV_TYPES) {
        // Compute how many tiles to place for specific env. type
        UINT envTiles(tiles * s_Config->m_LandTypeProp.proportionOf(envType));

        // Set constrains that are env. type specific
        constrs[2] = new Clustering(*s_Map,envType,s_Config->m_LandCompactness);

        // Generate tiles for specific env. type
        generateEnv(envType, envTiles, constrs, "Growing landmasses");

        // Delete constraints that are env. type specific
        delete constrs[2];
    }

    // Delete constraints that are common for all env. type
    delete constrs[0];
    delete constrs[1];
}

void MapGenerator::generateEnv(EnvType        i_Type,
                               UINT           i_NumElem,
                               const Constrs& i_Constr,
                               const char*    i_TaskDesc)
{
    // Progress logging
    std::stringstream ss;
    ss << "World generation - "<< i_TaskDesc <<" (" << ENV_NAMES[i_Type] << ")";
    std::string msg = ss.str();
    ProgressLogger progressLogger(i_NumElem, msg);

    UINT elemPlaced(0);
    
    // Loop until all needed tiles are placed
    while (elemPlaced < i_NumElem) {
        // Generate a random coord
		const Coord coord(randCoord());

        // At first, the probability of placing the env. is 100 %
		double totalProb(1.0);

        // Each constraint will reduce this probability 
        // (product of all constraint weights)
        for (auto constraint : i_Constr) {
            totalProb *= constraint->getWeightFor(coord);
		}

        // Generate a probability
		if (randProb() < totalProb) {
            // Set the env.
            UINT tileNum(coord.x + coord.y * s_Map->dim().x);
            s_Map->m_Tiles[tileNum].setEnvironment(i_Type);
            ++elemPlaced;
            progressLogger.next();
		}
	}
}

const Coord MapGenerator::randCoord()
{
    UINT obw(s_Config->m_OceanBorderWidth);
    int x(randUINT(obw, s_Config->m_Dim.x - 1 - 2 * obw));
    int y(randUINT(obw, s_Config->m_Dim.y - 1 - 2 * obw));
    return Coord(x, y);
}