#include <assert.h>
#include <Constraint.h>
#include <Elem2D.h>
#include <Environment.h>
#include <EnvironmentIs.h>
#include <FatalErrorDialog.h>
#include <JSONUtils.h>
#include <Map.h>
#include <MapGenerator.h>
#include <math.h>
#include <Parameters.h>
#include <Phase.h>
#include <ProgressLogger.h>
#include <Random.h>
#include <rapidjson\error\en.h>
#include <Tile.h>
#include <utility>
#include <vector>

using namespace rapidjson;

typedef std::pair<unsigned int, unsigned int> pairUINT;

namespace MapGenerator
{
    //= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
    //                                GENERATION                              //
    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

    // ----- Temporary variables ----- //

    // The map that is being generated
    Map*   s_Map;
    // Root node of the map configuration JSON file
    Value* s_JSONRoot;
    // Corners of alterable portion of the map (borders are unalterable)
    Coord  s_ULCorner;
    Coord  s_LRCorner;

    // ----- Global variables ----- //

    // Map dimensions extremum
    static pairUINT loadMapDimExtremum();
    static const pairUINT s_MapDimExtremum(loadMapDimExtremum());

    void generate(Map& o_Map, const char* i_MapConfigFile)
    {
        s_Map = &o_Map;

        // Parse rapidjson document
        Document m_Doc;
        s_JSONRoot = &parseJSON(m_Doc, i_MapConfigFile, CONFIG_ROOT_ELEM);

        // Initialize map tiles
        initializeMapTiles();

        // Place unalterable borders
        placeBorders();

        // Fill with initial biome
        fillWithInitialBiome();

        // Execute environment generation phases
        executeEnvironmentPhases();

        // Pass over to polish the map and add the natural ressources
        runOverpass();
    }

    void initializeMapTiles()
    {
        const Value& elem(parseSubElem(*s_JSONRoot, DIM_ELEM));
        s_Map->clearAndResize(parseMapDimension(elem, DIM_WIDTH_SUB_ELEM),
                              parseMapDimension(elem, DIM_HEIGHT_SUB_ELEM));
    }

    unsigned int parseMapDimension(const Value&i_Elem,const char* i_SubElemName)
    {
        unsigned int dim(parseUINT(i_Elem, i_SubElemName));
        if (dim < s_MapDimExtremum.first) {
            std::stringstream ss;
            ss << i_SubElemName << " of map is too small (minimum is " 
               << s_MapDimExtremum.first << ")";
            FatalErrorDialog(ss.str());
        }
        if (dim > s_MapDimExtremum.second) {
            std::stringstream ss;
            ss << i_SubElemName << " of map is too large (maximum is "
                << s_MapDimExtremum.second << ")";
            FatalErrorDialog(ss.str());
        }
        return dim;
    }

    void placeBorders()
    {
        // Set initial unalterable map zone (borders will reduce it)
        s_ULCorner = Coord(0, 0);
        s_LRCorner = Coord(s_Map->dimensions());

        // Parse border element
        const Value& elem(parseSubElem(*s_JSONRoot, BORDERS_ELEM));

        // For each border (the last one has the priority)
        for (auto it(elem.MemberBegin()); it != elem.MemberEnd(); ++it) {
            // Parse border side string name ("NORTH", "EAST"...) 
            const char* cardDir(it->name.GetString());

            // Check if string is a valid cardinal direction
            auto cardDirEntry(CARDINAL_DIRS.find(cardDir));
            if (cardDirEntry == CARDINAL_DIRS.end()) {
                std::stringstream ss;
                ss << "\"" << cardDir << "\" is not a valid cardinal direction";
                FatalErrorDialog(ss.str());
            }

            // Parse border sub-element
            const Value& subElem(parseSubElem(elem, cardDir));

            // Generate border
            generateBorder(parseBiome(subElem), cardDirEntry->second, 
                           cardDir, parseUINT(subElem, WIDTH_ELEM));
        }
    }

    void generateBorder(Biome i_Biome, BasicDir i_Side, 
                        const std::string& i_SideName, unsigned int i_Width)
    {
        // Skip ocean borders because tiles are ocean at initialization
        if (i_Biome == OCEAN) {
            return;
        }

        // Get map size
        unsigned int mapW(s_Map->width());
        unsigned int mapH(s_Map->height());

        // Generate potential error message
        static const std::string ERR_MSG(i_SideName + 
            " border cannot be larger than half of the map");

        // Check that border is not larger than half of map
        unsigned int limitDim((i_Side == UP || i_Side == DOWN) ? mapH : mapW);
        if (i_Width >= limitDim * 0.5) {
            FatalErrorDialog(ERR_MSG.c_str());
        }

        // Set border region corners and adjust unalterable map zone
        Coord ulCorner;
        Coord lrCorner;

        switch (i_Side) {
        case UP:
            ulCorner = Coord(0, 0); 
            lrCorner = Coord(mapW, i_Width);
            s_ULCorner.y = i_Width;
            break;
        case RIGHT:
            ulCorner = Coord(mapW - i_Width, 0); 
            lrCorner = Coord(mapW, mapH);
            s_LRCorner.x = mapW - i_Width;
            break;
        case DOWN:
            ulCorner = Coord(0, mapH - i_Width);
            lrCorner = Coord(mapW, mapH);
            s_LRCorner.y = mapH - i_Width;
            break;
        case LEFT:  
            ulCorner = Coord(0, 0);
            lrCorner = Coord(i_Width, mapH);
            s_ULCorner.x = i_Width;
            break;
        }

        // Fill the border
        fillBiomeRegion(i_Biome, ulCorner, lrCorner);
    }

    void fillWithInitialBiome()
    {
        // Parse init env type
        Biome biome(parseBiome(*s_JSONRoot, INIT_BIOME_ELEM));
        if (biome != OCEAN) {
            fillBiomeRegion(biome, s_ULCorner, s_LRCorner);
        }
    }

    void fillBiomeRegion(Biome i_Biome, Coord i_ULCorner, Coord i_LRCorner)
    {
        Coord coord;
        for (coord.y = i_ULCorner.y; coord.y < i_LRCorner.y; ++coord.y) {
            for (coord.x = i_ULCorner.x; coord.x < i_LRCorner.x; ++coord.x) {
                (*s_Map)(coord).setBiome(i_Biome);
            }
        }
    }

    void executeEnvironmentPhases()
    {
        // Parse phases
        const Value& elem(parseSubElem(*s_JSONRoot, PHASES_ELEM));
        
        // For every phase
        for (auto it = elem.MemberBegin(); it != elem.MemberEnd(); ++it) {
            Phase phase(*s_Map, it->name.GetString(), it->value);

            for (const auto& envCnstrnts : phase.m_Cnstrts) {
                unsigned int qty(envCnstrnts.second.first);
                unsigned int placed(0);
                unsigned int tries(0);

                // Progress logging
                std::stringstream ss;
                ss << "World generation - " << phase.m_Name << " - "
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
                    else if (++tries > phase.m_MaxTries) {
                        LOG(ERROR) << "Maximum number of tries reached."
                            << " Skipping phase for this environment.";
                        break;
                    }
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
        return Coord(randUINT(s_ULCorner.x, s_LRCorner.x - 1), 
                     randUINT(s_ULCorner.y, s_LRCorner.y - 1));
    }


    //= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
    //                          MAXIMUM MAP DIMENSIONS                        //
    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

    std::pair<unsigned int, unsigned int> loadMapDimExtremum()
    {
        Document doc;
        Value& root = parseJSON(doc, MAP_LIMITS, LIMITS_ROOT_ELEM);
        return std::make_pair(parseUINT(root, MIN_MAP_SIZE_ELEM),
                              parseUINT(root, MAX_MAP_SIZE_ELEM));
    }
}
