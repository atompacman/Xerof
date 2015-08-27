#include <assert.h>
#include <Constraint.h>
#include <Elem2D.h>
#include <Environment.h>
#include <FatalErrorDialog.h>
#include <JSONUtils.h>
#include <list>
#include <Map.h>
#include <MapGenerator.h>
#include <math.h>
#include <Parameters.h>
#include <ProgressLogger.h>
#include <Random.h>
#include <rapidjson\error\en.h>
#include <Tile.h>
#include <utility>
#include <vector>

using namespace rapidjson;

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
    std::pair<unsigned int, unsigned int> loadMapDimExtremum()
    {
        Document doc;
        Value& root = parseJSON(doc, MAP_LIMITS, LIMITS_ROOT_ELEM);
        return std::make_pair(parseUINT(root, MIN_MAP_SIZE_ELEM),
                              parseUINT(root, MAX_MAP_SIZE_ELEM));
    }
    static const std::pair<unsigned int, unsigned int> 
        s_MapDimExtremum = loadMapDimExtremum();


    // ----- Functions ----- //

    void generate(Map& o_Map, const std::string& i_MapConfigFile)
    {
        // Save a pointer to map
        s_Map = &o_Map;

        // Parse rapidjson document
        Document m_Doc;
        s_JSONRoot = &parseJSON(m_Doc, i_MapConfigFile, CONFIG_ROOT_ELEM);

        // Initialize map tiles
        const Value& dimElem(parseSubElem(*s_JSONRoot, DIM_ELEM));
        s_Map->clearAndResize(parseMapDimension(dimElem, DIM_WIDTH_SUB_ELEM),
                              parseMapDimension(dimElem, DIM_HEIGHT_SUB_ELEM));

        // Set initial unalterable map zone corners (borders will reduce it)
        s_ULCorner = Coord(0, 0);
        s_LRCorner = Coord(s_Map->dimensions());

        // Place unalterable borders
        const Value& borderElem(parseSubElem(*s_JSONRoot, BORDERS_ELEM));
        for (auto it=borderElem.MemberBegin(); it!=borderElem.MemberEnd();++it){
            placeBorder(it->value, it->name.GetString());
        }

        // Fill map with initial biome
        Biome biome(parseBiome(*s_JSONRoot, INIT_BIOME_ELEM));
        if (biome != OCEAN) {
            fillBiomeRegion(biome, s_ULCorner, s_LRCorner);
        }

        // Execute generation phases
        const Value& phasesElem(parseSubElem(*s_JSONRoot, PHASES_ELEM));
        for (auto it=phasesElem.MemberBegin(); it!=phasesElem.MemberEnd();++it){
            executePhase(it->value, it->name.GetString());
        }

        // Pass over to polish the map and add the natural ressources
        //runOverpass();
    }

    unsigned int parseMapDimension(const Value&       i_Elem,
                                   const std::string& i_SubElemName)
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

    void placeBorder(const Value& i_BorderElem, const std::string& i_SideName)
    {
        // Check if string is a valid cardinal direction
        auto cardDirEntry(CARDINAL_DIRS.find(i_SideName));
        if (cardDirEntry == CARDINAL_DIRS.end()) {
            std::stringstream ss;
            ss << "\"" << i_SideName << "\" is not a valid cardinal direction";
            FatalErrorDialog(ss.str());
        }

        // Parse biome
        Biome biome(parseBiome(i_BorderElem, BIOME_ELEM));

        // Skip ocean borders because tiles are ocean at initialization
        if (biome == OCEAN) {
            return;
        }

        // Parse width
        unsigned int width(parseUINT(i_BorderElem, WIDTH_ELEM));

        // Get map size
        unsigned int mapW(s_Map->width());
        unsigned int mapH(s_Map->height());

        // Check that border is not larger than half of map
        BasicDir side(cardDirEntry->second);
        unsigned int limitDim((side == UP || side == DOWN) ? mapH : mapW);
        if (width >= limitDim * 0.5) {
            FatalErrorDialog((i_SideName +
                " border cannot be larger than half of the map").c_str());
        }

        // Set border region corners and adjust unalterable map zone
        Coord ulCorner;
        Coord lrCorner;

        switch (side) {
        case UP:
            ulCorner = Coord(0, 0);
            lrCorner = Coord(mapW, width);
            s_ULCorner.y = width;
            break;
        case RIGHT:
            ulCorner = Coord(mapW - width, 0);
            lrCorner = Coord(mapW, mapH);
            s_LRCorner.x = mapW - width;
            break;
        case DOWN:
            ulCorner = Coord(0, mapH - width);
            lrCorner = Coord(mapW, mapH);
            s_LRCorner.y = mapH - width;
            break;
        case LEFT:
            ulCorner = Coord(0, 0);
            lrCorner = Coord(width, mapH);
            s_ULCorner.x = width;
            break;
        }

        // Fill the border
        fillBiomeRegion(biome, ulCorner, lrCorner);
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

    void executePhase(const Value& i_PhaseElem, const std::string i_PhaseName)
    {
        // Parse total number of tiles to change
        unsigned int totalQty(parsePhaseQtyElem(i_PhaseElem));

        // Parse maximum number of tries
        unsigned int maxTries(parseUINT(i_PhaseElem, MAX_TRIES_ELEM));
        maxTries = maxTries == 0 ? (unsigned int)-1 : maxTries;

        // Parse constraints
        std::list<Constraint*> cnstrnts;
        const Value& cnstElem(parseSubElem(i_PhaseElem, CONSTRAINTS_ELEM));
        for (auto it(cnstElem.MemberBegin()); it != cnstElem.MemberEnd(); ++it){
            // Find constraint factory method
            std::string cnstrntName(it->name.GetString());
            auto entry(Constraint::s_Factory.find(cnstrntName));
            if (entry == Constraint::s_Factory.end()) {
                std::stringstream ss;
                ss << "Invalid constraint \"" << cnstrntName << "\"";
                FatalErrorDialog(ss.str());
            }

            // Call factory method
            cnstrnts.push_back((entry->second)(it->value, *s_Map));
        }

        // For each element
        double sum(0);
        const Value& elemProp(parseSubElem(i_PhaseElem, BIOMES_PROP_ELEM));
        for (auto it = elemProp.MemberBegin(); it != elemProp.MemberEnd();++it){
            auto entry(STR_TO_BIOME.find(it->name.GetString()));

            // Check if string element is valid
            if (entry == STR_TO_BIOME.end()) {
                std::stringstream ss;
                ss << "Invalid element \"" << it->name.GetString() << "\"";
                FatalErrorDialog(ss.str());
            }
            Biome elem(entry->second);

            // Parse element placement proportion
            double prop(it->value.GetDouble());
            sum += prop;
            double elemQty = (unsigned int)rint(prop * (double)totalQty);

            // Execute phase for specific element
            executePhaseForElement(elem,cnstrnts,i_PhaseName,elemQty,maxTries);
        }

        // Check if proportions sum to 1
        if (!almostEqual(sum, 1)) {
            FatalErrorDialog("Element proportions do not sum to 1");
        }
    }

    void executePhaseForElement(Biome                         i_Element,
                                const std::list<Constraint*>& i_Constraints,
                                const std::string             i_PhaseName,
                                unsigned int                  i_ElemQty,
                                unsigned int                  i_MaxTries)
    {
        unsigned int placed(0);
        unsigned int tries(0);

        // Init progress logger
        std::stringstream ss;
        ss << "World generation - " << i_PhaseName << " - "
            << ENV_NAMES[i_Element] << " [" << i_ElemQty << " tiles]";
        std::string msg = ss.str();
        ProgressLogger progressLogger(i_ElemQty, msg);

        // Loop until all needed tiles are placed
        while (placed < i_ElemQty) {
            // Generate a random coord
            const Coord coord(randCoord());

            // At first, the probability of placing the env. is 100 %
            double totalProb(1.0);

            // Each constraint will reduce this probability 
            // (product of all constraint weights)
            for (const auto& constraint : i_Constraints) {
                totalProb *= constraint->evaluate(i_Element, coord);
            }

            // Generate a probability
            if (randProb() < totalProb) {
                // Set the env.
                (*s_Map)(coord).setBiome(i_Element);
                ++placed;
                progressLogger.next();
            }
            else if (++tries > i_MaxTries) {
                LOG(ERROR) << "Maximum number of tries reached."
                    << " Skipping phase for this environment.";
                break;
            }
        }
    }

    unsigned int parsePhaseQtyElem(const Value& i_PhaseElem)
    {
        const Value& qtyElem(parseSubElem(i_PhaseElem, QTY_ELEM));

        if (qtyElem.HasMember(RELATIVE_ELEM.c_str())) {
            double relQty(parseDouble(qtyElem, RELATIVE_ELEM));
            return (unsigned int)(relQty*s_Map->area() + 0.5);
        }

        if (qtyElem.HasMember(ABSOLUTE_ELEM.c_str())) {
            return parseUINT(qtyElem, ABSOLUTE_ELEM);
        }

        std::stringstream ss;
        ss << "Expecting a \"" << RELATIVE_ELEM << "\" or a \""
            << ABSOLUTE_ELEM << "\" element for " << QTY_ELEM << " element";
        FatalErrorDialog(ss.str());
        return 0;
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
}
