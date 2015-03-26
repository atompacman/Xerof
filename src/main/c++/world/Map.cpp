#include "Map.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Map::Map() :
m_Tiles(new Tile*[area(MAP_DIMENSIONS)])
{
    // For progression bar
    UINT n = area(MAP_DIMENSIONS) / PGI;
    UINT progres = 0;
    //

    for (UINT i = 0; i < area(MAP_DIMENSIONS); ++i) {
        Tile * tile = new Tile();
        tile->setEnvironment(OCEAN);
        m_Tiles[i] = tile;
        LOG_EVERY_N(n, DEBUG) << "World generation - Allocating tiles "
            << "to memory [" << std::setw(3) << ++progres * PGI << "%]";
    }

	assert(INITIAL_LAND_TILES < LAND_TILES);
	assert(TUNDRA_PROPORTION < 1.0);
	assert(TUNDRA_RANDOMNESS_RADIUS < MAP_DIMENSIONS.y / 2);
	m_PlacedInitPlains = 0;
	m_PlacedInitRockies = 0;

	initWorldGeneratorSeed();
	generateLand();
}

void Map::generateLand()
{
    assert(INITIAL_LAND_TILES <= LAND_TILES);
    placeInitialLandTiles();
    growIslands();
}

void Map::placeInitialLandTiles()
{
    // For progression bar
    UINT n = INITIAL_LAND_TILES / PGI;
    UINT progres = 0;
    //

    UINT placedTiles = 0;

    while (placedTiles < INITIAL_LAND_TILES) {
        Coord coord = randTile();
        double distanceWeight = computeDistanceWeight(coord);
        if (nextRand(100) < distanceWeight * 100.0 && !isLand(coord)) {
            setLandTile(coord);
            ++placedTiles;
            LOG_EVERY_N(n, DEBUG) << "World generation - Placing initial "
                << "land tiles [" << std::setw(3) << ++progres * PGI << "%]";
        }
    }
}

void Map::growIslands()
{
    // For progression bar
    UINT n = (LAND_TILES - INITIAL_LAND_TILES) / PGI;
    UINT progres = 0;
    //

    UINT placedTiles = INITIAL_LAND_TILES;

    while (placedTiles < LAND_TILES) {
        Coord coord = randTile();
        double distanceWeight = computeDistanceWeight(coord);
        double surroundingLandWeight = computeSurroundingLandWeight(coord);
        double weightedProb = distanceWeight * surroundingLandWeight;

        if (nextRand(100) < weightedProb * 100.0 && !isLand(coord)) {
            setLandTile(coord);
            ++placedTiles;
            LOG_EVERY_N(n, DEBUG) << "World generation - Placing land "
                << "tiles [" << std::setw(3) << ++progres * PGI << "%]";
        }
    }
}

void Map::setLandTile(Coord i_Coord)
{
    int randomizedHeigth = i_Coord.y
        + nextRand(0-TUNDRA_RANDOMNESS_RADIUS, TUNDRA_RANDOMNESS_RADIUS);

    if (distFromEquatorProportion(randomizedHeigth) > (1 - TUNDRA_PROPORTION)) {
        setEnvironnement(i_Coord, TUNDRA);
    }
    else if (suitablePlainLocation(i_Coord)) {
        setEnvironnement(i_Coord, PLAIN);
    }
    else if (suitableRockyLocation(i_Coord)) {
        setEnvironnement(i_Coord, ROCKY);
    }
    else {
        setEnvironnement(i_Coord, GRASSLAND);
    }
}

bool Map::suitablePlainLocation(Coord i_Coord)
{
    if (m_PlacedInitPlains < INITIAL_PLAIN_TILES) {
        ++m_PlacedInitPlains;
        return nextRand(100) < computeAltitudeWeight(i_Coord.y) * 100.0;
    }
    if (hasSurroundingTileOfType(i_Coord, PLAIN)) {
        return nextRand(100) < computeAltitudeWeight(i_Coord.y) * 100.0;
    }
    return false;
}

bool Map::suitableRockyLocation(Coord i_Coord)
{
    if (m_PlacedInitPlains == INITIAL_PLAIN_TILES &&
        m_PlacedInitRockies < INITIAL_ROCKY_TILES) {
        ++m_PlacedInitRockies;
        return true;
    }

    int surroundingRockyTiles = countSurroundingTilesOfType(i_Coord, ROCKY);

    if (surroundingRockyTiles > 0 &&
        nextRand(100) < ROCKY_TILES_PROPORTION * 100 &&
        surroundingRockyTiles < ROCKY_ZONE_THICKNESS) {
        return true;
    }
    return false;
}

bool Map::isLand(Coord i_Coord) const
{
    return getTile(i_Coord)->getEnvironment()->isSolidLand();
}

Map::~Map()
{
	delete[] m_Tiles;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   SETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Map::setEnvironnement(Coord i_Coord, EnvType i_Type)
{
	getTile(i_Coord)->setEnvironment(i_Type);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Tile* Map::getTile(Coord i_Coord) const
{
	assert(i_Coord.x < MAP_DIMENSIONS.x);
	assert(i_Coord.y < MAP_DIMENSIONS.y);
	return m_Tiles[linearize(i_Coord)];
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                  DISTANCE                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

double Map::computeDistanceWeight(Coord i_Coord) const
{
	double xMapRadius = MAP_DIMENSIONS.x / 2.0;
	double yMapRadius = MAP_DIMENSIONS.y / 2.0;
	double xWeight = 1 - abs((double)i_Coord.x - xMapRadius) / xMapRadius;
	double yWeight = 1 - abs((double)i_Coord.y - yMapRadius) / yMapRadius;

	return pow(xWeight * yWeight, DISTANCE_CRITERIA_WEIGHT);
}

double Map::computeAltitudeWeight(int i_Y) const
{
	return pow(1 - distFromEquatorProportion(i_Y), PLAIN_ALTITUDE_WEIGHT);
}

double Map::distFromEquatorProportion(int i_Y) const
{
	double distFromEquator = abs((double)i_Y - (double)MAP_DIMENSIONS.y / 2);
	return distFromEquator / ((double)MAP_DIMENSIONS.y / 2);
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                               SURROUNDING TILES                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

double Map::computeSurroundingLandWeight(Coord i_Coord) const
{
	int landTiles = countSurroundingLandTiles(i_Coord);
	return pow(((double)landTiles) / 8.0, SURROUNDING_LAND_CRITERIA_WEIGHT);
}

bool Map::hasSurroundingLand(Coord i_Coord) const
{
	return countSurroundingLandTiles(i_Coord) != 0;
}

bool Map::hasSurroundingTileOfType(Coord i_Coord, EnvType i_Type) const
{
	return countSurroundingTilesOfType(i_Coord, i_Type) != 0;
}

UINT Map::countSurroundingLandTiles(Coord i_Coord) const
{
	int count = 0;
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			if (isLand(Coord(i_Coord.x + x, i_Coord.y + y))) {
				++count;
			}
		}
	}
	return count;
}

UINT Map::countSurroundingTilesOfType(Coord i_Coord, EnvType i_Type) const
{
	int count = 0;
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			const Tile* tile = getTile(Coord(i_Coord.x + x, i_Coord.y + y));
			if (tile->getEnvironment()->getType() == i_Type) {
				++count;
			}
		}
	}
	return count;
}