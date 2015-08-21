#include <assert.h>
#include <Constraint.h>
#include <DistanceFromCenter.h>
#include <Environment.h>
#include <EnvironmentIs.h>
#include <Map.h>
#include <MapConfig.h>
#include <MapGenerator.h>
#include <math.h>
#include <ProgressLogger.h>
#include <Random.h>
#include <Tile.h>
#include <vector>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                  GENERATION                                //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

namespace MapGenerator
{
    Map*       s_Map;
    MapConfig* s_Config;
    Coord      s_ULCorner;
    Coord      s_LRCorner;

    void generate(Map& o_Map)
    {
        generate(o_Map, DEFAULT_MAP_CONFIG);
    }

    void generate(Map& o_Map, const char* i_MapConfigFile)
    {
        // Read config file
        s_Config = new MapConfig(i_MapConfigFile);

        // Initialized map with dimensions specified by the config file
        s_Map = &o_Map;
        s_Map->clearAndResize(s_Config->m_Dim);

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
        runOverpass();

        // Delete map config
        delete s_Config;
    }

    void placeBorders()
    {
        // Zone that will be filled by the initial env 
        // (borders may reduce this space)
        s_ULCorner = Coord(0, 0);
        s_LRCorner = Coord(s_Map->dimensions());

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
            if (border.m_Biome == OCEAN) {
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
                for (coord.y = 0; coord.y < border.m_Width; ++coord.y) {
                    for (coord.x = 0; coord.x < mapW; ++coord.x) {
                        (*s_Map)(coord).setBiome(border.m_Biome);
                    }
                }
                break;
            case DOWN:
                if (border.m_Width >= mapH * 0.5) {
                    FatalErrorDialog("South border cannot be \
                                      larger than half of the map");
                }
                for (coord.y = mapH-border.m_Width; coord.y < mapH; ++coord.y) {
                    for (coord.x = 0; coord.x < s_Map->width(); ++coord.x) {
                        (*s_Map)(coord).setBiome(border.m_Biome);
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
                        (*s_Map)(coord).setBiome(border.m_Biome);
                    }
                }
                break;
            case RIGHT:
                if (border.m_Width > mapW * 0.5) {
                    FatalErrorDialog("East border cannot be \
                                      larger than half of the map");
                }
                for (coord.y = 0; coord.y < mapH; ++coord.y) {
                    for (coord.x = mapW-border.m_Width; coord.x<mapW;++coord.x){
                        (*s_Map)(coord).setBiome(border.m_Biome);
                    }
                }
                break;
            }
        }
    }

    void fillWithInitEnv()
    {
        if (s_Config->m_InitEnvType == OCEAN) {
            // Tiles are already ocean
            return;
        }

        Coord coord;
        for (coord.y = s_ULCorner.y; coord.y < s_LRCorner.y; ++coord.y) {
            for (coord.x = s_ULCorner.x; coord.x < s_LRCorner.x; ++coord.x) {
                (*s_Map)(coord).setBiome(s_Config->m_InitEnvType);
            }
        }
    }

    void executeMapGenPhase(const Phase& i_Phase)
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
                    (*s_Map)(coord).setBiome(envCnstrnts.first);
                    ++placed;
                    progressLogger.next();
                }
                else if (++tries > i_Phase.m_MaxTries) {
                    LOG(ERROR) << "Maximum number of tries reached."
                        << " Skipping phase for this environment.";
                    break;
                }
            }
        }
    }

    void runOverpass()
    {
        int numTileTraveled = 1;
        Coord readCoord(0, 0);
        int divisor = 2;
        int addedToCoord = 0;
        bool addToX = true;

        LOG(INFO) << "Start of overpass";

        // We stop reading when we reach the bottom right corner
        while (readCoord.x < s_LRCorner.x || readCoord.y < s_LRCorner.y){

            // calculation of the next coordinate

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

            removeLonelyTiles(OCEAN, readCoord);
        }

        LOG(INFO) << "End of overpass";
    }

    void removeLonelyTiles(const Biome& i_ChangedBiome,
                           const Coord& i_ReadCoord)
    {
        Coord surroundingCoord[8] = { Coord(-1, -1), Coord(0, -1), Coord(1, -1),
            Coord(-1, 0), Coord(1, 0), Coord(-1, 1), Coord(0, 1), Coord(1, 1) };
        Coord tempCoord;
        bool tileChange = false;
        int randomNumber;

        // if we are outside the map nothing is done
        if (i_ReadCoord < s_Map->dimensions())
        {

            // Modification of lonely ocean biome
            if ((*s_Map)(i_ReadCoord).getEnvironment().getBiome()
                == i_ChangedBiome)
            {
                tileChange = true;

                // we travel the surrounding tile to look for a second ocean
                for (int i = 0; i < 8; ++i)
                {
                    tempCoord = i_ReadCoord + surroundingCoord[i];

                    // verification to make sure we're not outside the map limit
                    if (tempCoord < s_Map->dimensions())
                    {
                        if ((*s_Map)(tempCoord).getEnvironment().getBiome()
                            == i_ChangedBiome)
                        {
                            tileChange = false;
                        }
                    }

                }
                // If tile change we find a random biome from surrounding tile
                if (tileChange)
                {
                    randomNumber = randUINT(0, 7);

                    tempCoord = i_ReadCoord + surroundingCoord[randomNumber];

                    // verification to make sure we're not outside the map limit
                    if (tempCoord < s_Map->dimensions())
                    {
                        (*s_Map)(i_ReadCoord).setBiome((*s_Map)(tempCoord)
                            .getEnvironment().getBiome());
                    }
                }
            }
        }
    }

    const Coord randCoord()
    {
        unsigned int x(randUINT(s_ULCorner.x, s_LRCorner.x - 1));
        unsigned int y(randUINT(s_ULCorner.y, s_LRCorner.y - 1));
        return Coord(x, y);
    }
}
