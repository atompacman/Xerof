#include <assert.h>
#include <Constraint.h>
#include <DistanceFromCenter.h>
#include <Environment.h>
#include <EnvironmentIs.h>
#include <Map.h>
#include <MapConfig.h>
#include <MapGenerator.h>
#include <ProgressLogger.h>
#include <Random.h>
#include <math.h>
#include <Tile.h>
#include <vector>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                  GENERATION                                //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Map*       MapGenerator::s_Map      = NULL;
MapConfig* MapGenerator::s_Config   = NULL;
Coord      MapGenerator::s_ULCorner;
Coord      MapGenerator::s_LRCorner;

Map& MapGenerator::generate()
{
    return generate(DEFAULT_MAP_CONFIG);
}

Map& MapGenerator::generate(const char* i_MapConfigFile)
{
    // Read config file
    s_Config = new MapConfig(i_MapConfigFile);

    // Initialized map with dimensions specified by the config file
    s_Map = new Map(s_Config->m_Dim);

    // Build map constraints from the config file
    s_Config->buildConstraints(*s_Map);

    // Initialize environments
    placeBorders();

    // Fill with initial environment
    fillWithInitEnv();

    // Execute map generation phases
    for (const Phase& phase : s_Config->m_Phases) {
        executeMapGenPhase(phase);
    }

    // Pass over to polish the map and add the natural ressources
    overpass();

    // Delete map config
    delete s_Config;

    return *s_Map;
}

void MapGenerator::placeBorders()
{
    // Zone that will be filled by the initial env 
    // (borders may reduce this space)
    s_ULCorner = Coord(0, 0);
    s_LRCorner = Coord(s_Map->m_Dim);

    // Get map size
    unsigned int mapW(s_Map->width());
    unsigned int mapH(s_Map->height());


    // Borders overlap each other (the last one has the priority)
    for (Border border : s_Config->m_Borders) {
        // Adjust generation zone
        switch (border.m_Side) {
        case UP:    s_ULCorner.y = border.m_Width; break;
        case DOWN:  s_LRCorner.y = mapH - border.m_Width; break;
        case LEFT:  s_ULCorner.x = border.m_Width; break;
        case RIGHT: s_LRCorner.x = mapW - border.m_Width; break;
        }

        // Skip ocean borders because tiles are ocean at initialization
        if (border.m_Env == OCEAN) {
            // Tiles are already ocean
            continue;
        }

        // Generate borders
        Coord coord;
        switch (border.m_Side) {
        case UP:
            if (border.m_Width >= mapH * 0.5) {
                FatalErrorDialog("North border cannot be \
                                  larger than half of the map");
            }
            for (    coord.y = 0; coord.y < border.m_Width; ++coord.y) {
                for (coord.x = 0; coord.x < mapW;           ++coord.x) {
                    (*s_Map)(coord).setEnvironment(border.m_Env);
                }
            }
            break;
        case DOWN:
            if (border.m_Width >= mapH * 0.5) {
                FatalErrorDialog("South border cannot be \
                                  larger than half of the map");
            }
            for (    coord.y = mapH - border.m_Width; coord.y < mapH;++coord.y){
                for (coord.x = 0; coord.x < s_Map->width(); ++coord.x) {
                    (*s_Map)(coord).setEnvironment(border.m_Env);
                }
            }
            break;
        case LEFT:
            if (border.m_Width > mapW * 0.5) {
                FatalErrorDialog("West border cannot be \
                                  larger than half of the map");
            }
            for (coord.y = 0; coord.y < mapH; ++coord.y) {
                for (coord.x = 0; coord.x < border.m_Width; ++coord.x) {
                    (*s_Map)(coord).setEnvironment(border.m_Env);
                }
            }
            break;
        case RIGHT:
            if (border.m_Width > mapW * 0.5) {
                FatalErrorDialog("East border cannot be \
                                  larger than half of the map");
            }
            for (coord.y = 0; coord.y < mapH; ++coord.y) {
                for (coord.x = mapW - border.m_Width; coord.x<mapW; ++coord.x) {
                    (*s_Map)(coord).setEnvironment(border.m_Env);
                }
            }
            break;
        }
    }
}

void MapGenerator::fillWithInitEnv()
{
    if (s_Config->m_InitEnvType == OCEAN) {
        // Tiles are already ocean
        return;
    }

    Coord coord;
    for (coord.y = s_ULCorner.y; coord.y < s_LRCorner.y; ++coord.y) {
        for (coord.x = s_ULCorner.x; coord.x < s_LRCorner.x; ++coord.x) {
            (*s_Map)(coord).setEnvironment(s_Config->m_InitEnvType);
        }
    }
}

void MapGenerator::executeMapGenPhase(const Phase& i_Phase)
{
    for (const auto& envCnstrnts : i_Phase.m_Cnstrts) {
        unsigned int qty(envCnstrnts.second.first);
        unsigned int placed(0);
        unsigned int tries(0);

        // Progress logging
        std::stringstream ss;
        ss << "World generation - " << i_Phase.m_Name << " - " 
            << ENV_NAMES[envCnstrnts.first] << " [" << qty << " tiles]";
        std::string msg = ss.str();
        ProgressLogger progressLogger(qty, msg);

        // Loop until all needed tiles are placed
        while (placed < qty) {
            // Generate a random coord
            const Coord coord(randCoord());

            // At first, the probability of placing the env. is 100 %
            double totalProb(1.0);

            // Each constraint will reduce this probability 
            // (product of all constraint weights)
            for (const auto& constraint : envCnstrnts.second.second) {
                totalProb *= constraint->getWeightFor(coord);
            }

            // Generate a probability
            if (randProb() < totalProb) {
                // Set the env.
                (*s_Map)(coord).setEnvironment(envCnstrnts.first);
                ++placed;
                progressLogger.next();
            }
            else if (++tries > i_Phase.m_MaxTries) {
                LOG(ERROR) << "Maximum number of tries reached."
                           << " Skipping phase for this environent.";
                break;
            }
        }
    }
}

void MapGenerator::overpass()
{
    int numTileTraveled = 1;
    Coord readCoord(0, 0);
    int divisor = 2;
    int addedToCoord = 0;
    bool addToX = true;

    //Biome bushBiome = GRASSLAND;
    //int bushBiomeCounter = 0;
    //unsigned int probabilitOfBush = 7;

    bool lastTileOcean = true;
    Coord surroundingCoord[8] = { Coord(0, 1), Coord(1, 0), Coord(0, -1), 
     Coord(0, -1), Coord(-1, 0), Coord(-1, 0), Coord(0, 1), Coord(0, 1) };
    int xAroundRandCoord[8] = { -1,  0,  1, -1, 1, -1, 0, 1 };
    int yAroundRandCoord[8] = { -1, -1, -1,  0, 0,  1, 1, 1 };
    Coord tempCoord;
    bool tileChange = false;
    int randomNumber;

    LOG(INFO) << "Start of overpass";

    // We stop reading when we reach the bottom right corner
    while (!(readCoord < s_LRCorner)){
        // ---------------------------------------------------------------------
        // calculation of the next coordinate
        // ---------------------------------------------------------------------
        // if the number of tile traveled is even the addition is the same
        if (numTileTraveled % 2 != 0)
        {
            ++readCoord.x;
        }
        else 
        {
            // find the highest n of 2^n that can divide the numTileTraveled
            while (numTileTraveled % divisor == 0)
            {
                divisor *= 2;
            }
            // multiplied once too much
            divisor = (log2(divisor)) - 1;
            

            if (divisor % 2 == 0)
            {
                addToX = false;
            }
            else
            {
                addToX = true;
                ++divisor;
            }

            addedToCoord = (pow(2, (divisor / 2))) - 1;

            if (addToX)
            {
                readCoord.x -= addedToCoord;
                ++readCoord.y;
            }
            else
            {
                readCoord.y -= addedToCoord;
                ++readCoord.x;
            }

            divisor = 2;
        }

        ++numTileTraveled;

        // ---------------------------------------------------------------------
        // Tile read
        // ---------------------------------------------------------------------
        // if we are outside the map nothing is done
        if (readCoord < s_Map->m_Dim)
        {
            //// add the bushes
            //if ((*s_Map)(readCoord).getEnvironment().getBiome() == bushBiome)
            //{
            //    // place bushes following a binomial distribution
            //    if (randUINT(1, probabilitOfBush) == 1)
            //    {
            //        // Add a bush to the tile
            //    }
            //}

            // Modification of lonely ocean biome
            if ((*s_Map)(readCoord).getEnvironment().getBiome() == OCEAN)
            {
                tempCoord = readCoord;
                tileChange = true;

                // we travel the surrounding tile to look for a second ocean
                for (int i = 0; i < 8; ++i)
                {
                    tempCoord += surroundingCoord[i];

                    // verification to make sure we're not outside the map limit
                    if (tempCoord < s_Map->m_Dim)
                    {
                        if ((*s_Map)(tempCoord).getEnvironment().getBiome() == OCEAN)
                        {
                            tileChange = false;
                        }
                    }

                }
                // If tile change we find a random biome from surrounding tile
                if (tileChange)
                {
                    randomNumber = randUINT(0, 7);

                    tempCoordX = coordX + xAroundRandCoord[randomNumber];
                    tempCoordY = coordY + yAroundRandCoord[randomNumber];

                    // verification to make sure we're not outside the map limit
                    if (tempCoord < s_Map->m_Dim)
                    {
                        (*s_Map)(tempCoord).setEnvironment((*s_Map)(tempCoord)
                            .getEnvironment().getBiome());
                    }
                }
            }
        }
    }

    LOG(INFO) << "End of overpass";
}

const Coord MapGenerator::randCoord()
{
    unsigned int x(randUINT(s_ULCorner.x, s_LRCorner.x - 1));
    unsigned int y(randUINT(s_ULCorner.y, s_LRCorner.y - 1));
    return Coord(x, y);
}