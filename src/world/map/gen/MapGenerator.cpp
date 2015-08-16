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

    // Borders overlap each other (the last one has the priority)
    for (Border border : s_Config->m_Borders) {
        // Adjust generation zone
        switch (border.m_Side) {
        case UP:    s_ULCorner.y = border.m_Width; break;
        case DOWN:  s_LRCorner.y = s_Map->m_Dim.y - border.m_Width; break;
        case LEFT:  s_ULCorner.x = border.m_Width; break;
        case RIGHT: s_LRCorner.x = s_Map->m_Dim.x - border.m_Width; break;
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
            if (border.m_Width > s_Map->m_Dim.y * 0.5) {
                FatalErrorDialog("North border cannot be \
                                  larger than half of the map");
            }
            for (unsigned int i = 0; i < border.m_Width * s_Map->m_Dim.x; ++i) {
                s_Map->m_Tiles[i].setEnvironment(border.m_Env);
            }
            break;
        case DOWN:
            if (border.m_Width > s_Map->m_Dim.y * 0.5) {
                FatalErrorDialog("South border cannot be \
                                  larger than half of the map");
            }
            for (unsigned int i(s_Map->m_Dim.x * s_Map->m_Dim.y - 
                border.m_Width * s_Map->m_Dim.x); 
                i < s_Map->m_Dim.x * s_Map->m_Dim.y; ++i) {
                s_Map->m_Tiles[i].setEnvironment(border.m_Env);
            }
            break;
        case LEFT:
            if (border.m_Width > s_Map->m_Dim.x * 0.5) {
                FatalErrorDialog("West border cannot be \
                                  larger than half of the map");
            }
            for (coord.y = 0; coord.y < s_Map->m_Dim.y; ++coord.y) {
                for (coord.x = 0; coord.x < border.m_Width; ++coord.x) {
                    s_Map->m_Tiles[coord.x + coord.y * s_Map->m_Dim.x].
                        setEnvironment(border.m_Env);
                }
            }
            break;
        case RIGHT:
            if (border.m_Width > s_Map->m_Dim.x * 0.5) {
                FatalErrorDialog("East border cannot be \
                                  larger than half of the map");
            }
            unsigned int dimX(s_Map->m_Dim.x);
            for (coord.y = 0; coord.y < s_Map->m_Dim.y; ++coord.y) {
                for (coord.x = dimX - border.m_Width; coord.x<dimX; ++coord.x) {
                    s_Map->m_Tiles[coord.x + coord.y * s_Map->m_Dim.x].
                        setEnvironment(border.m_Env);
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
            s_Map->m_Tiles[coord.x + coord.y * s_Map->m_Dim.x].
                setEnvironment(s_Config->m_InitEnvType);
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
                s_Map->m_Tiles[coord.x + coord.y * s_Map->m_Dim.x]
                    .setEnvironment(envCnstrnts.first);
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
    int nbCaseParcourue = 1;
    unsigned int coordX = 0;
    unsigned int coordY = 0;
    int diviseur = 2;
    int valeurDeplacement = 0;
    bool addToX = true;

    Biome bushBiome = GRASSLAND;
    int bushBiomeCounter = 0;
    unsigned int probabilitOfBush = 7;

    bool lastTileOcean = true;
    int xAroundCoord[8] = { 0, 1,  0,  0, -1, -1, 0, 0 };
    int yAroundCoord[8] = { 1, 0, -1, -1,  0,  0, 1, 1 };
    int xAroundRandCoord[8] = { -1,  0,  1, -1, 1, -1, 0, 1 };
    int yAroundRandCoord[8] = { -1, -1, -1,  0, 0,  1, 1, 1 };
    unsigned int tempCoordX;
    unsigned int tempCoordY;
    bool tileChange = false;
    int randomNumber;

    LOG(INFO) << "Start of overpass";

    // We stop reading when we reach the bottom right corner
    while (coordX < s_LRCorner.x || coordY < s_LRCorner.y){

        // calculation of the next coordinate
        // si le nombre est impaire l'addition est toujours la meme
        if (nbCaseParcourue % 2 != 0)
        {
            ++coordX;
        }
        else 
        {
            while (nbCaseParcourue % diviseur == 0)
            {
                diviseur *= 2;
            }

            // on a multiplié une fois de trop donc on réduit l'exposant de 1
            diviseur = (log2(diviseur)) - 1;

            if (diviseur % 2 == 0)
            {
                addToX = false;
            }
            else
            {
                addToX = true;
                ++diviseur;
            }

            valeurDeplacement = (pow(2, (diviseur / 2))) - 1;

            if (addToX)
            {
                coordX -= valeurDeplacement;
                ++coordY;
            }
            else
            {
                coordY -= valeurDeplacement;
                ++coordX;
            }

            diviseur = 2;
        }

        ++nbCaseParcourue;

        // if we are outside the map nothing is done
        if (coordX < s_Map->m_Dim.x && coordY < s_Map->m_Dim.y)
        {
            // add the bushes
            if (s_Map->getTile(Coord(coordX, coordY)).getEnvironment()
                .getBiome() == bushBiome)
            {
                // place bushes following a binomial distribution
                if (randUINT(1, probabilitOfBush) == 1)
                {
                    // Add a bush to the tile
                }
            }

            // Modification of lonely ocean biome
            if (s_Map->getTile(Coord(coordX, coordY)).getEnvironment()
                .getBiome() == OCEAN)
            {
                tempCoordX = coordX;
                tempCoordY = coordY;
                tileChange = true;

                // we travel the surrounding tile to look for a second ocean
                for (int i = 0; i < 8; ++i)
                {
                    tempCoordX += xAroundCoord[i];
                    tempCoordY += yAroundCoord[i];

                    // verification to make sur we're not outside the map limit
                    if (tempCoordX < s_Map->m_Dim.x 
                        && tempCoordY < s_Map->m_Dim.y)
                    {
                        if (s_Map->getTile(Coord(tempCoordX, tempCoordY))
                            .getEnvironment().getBiome() == OCEAN)
                        {
                            tileChange = false;
                        }
                    }

                }
                // if the tile change we find a random tile around and change 
                // the biome to the selected tile biome
                if (tileChange)
                {
                    randomNumber = randUINT(0, 7);

                    tempCoordX = coordX + xAroundRandCoord[randomNumber];
                    tempCoordY = coordY + yAroundRandCoord[randomNumber];

                    // verification to make sur we're not outside the map limit
                    if (tempCoordX < s_Map->m_Dim.x 
                        && tempCoordY < s_Map->m_Dim.y)
                    {
                        s_Map->getTile(Coord(coordX, coordY)).setEnvironment(
                            s_Map->getTile(Coord(tempCoordX, tempCoordY))
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