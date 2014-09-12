#include "Map.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Map::Map()
{
	tiles = new Tile*[MAP_DIMENSIONS.area()];

	int tileNo = 0;
	Coord<int> coord = Coord<int>();

	for (coord.y = 0; coord.y < MAP_DIMENSIONS.y; ++coord.y) {
		for (coord.x = 0; coord.x < MAP_DIMENSIONS.x; ++coord.x) {
			Tile * tile = new Tile();
			tile->setEnvironnement(OCEAN);
			tiles[linearize(coord)] = tile;
			++tileNo;
			if (DEBUG_MODE && VERBOSE >= 2 && tileNo % 1000 == 0) {
				fprintf(stdout, "[%d/%d] tiles allocated in memory.\n",
					tileNo, MAP_DIMENSIONS.area());
			}
		}
	}

	assert(INITIAL_LAND_TILES < LAND_TILES);
	assert(TUNDRA_PROPORTION < 1.0);
	assert(TUNDRA_RANDOMNESS_RADIUS < MAP_DIMENSIONS.y / 2);
	placedInitialPlainTiles = 0;
	placedInitialRockyTiles = 0;

	initWorldGeneratorSeed();
	generateLand();
}

Map::~Map()
{
	Coord<int> coord = Coord<int>();

	for (coord.y = 0; coord.y < MAP_DIMENSIONS.y; ++coord.y) {
		for (coord.x = 0; coord.x < MAP_DIMENSIONS.x; ++coord.x) {
			delete getTile(coord);
		}
	}
	delete[] tiles;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   SETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

void Map::setEnvironnement(Coord<int> coord, EnvType type)
{
	getTile(coord)->setEnvironnement(type);
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   GETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

Tile* Map::getTile(Coord<int> coord) const
{
	assert(coord.x < MAP_DIMENSIONS.x);
	assert(coord.y < MAP_DIMENSIONS.y);
	return tiles[linearize(coord)];
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//               MAP GENERATION                //
//- - - - - - - - - - - - - - - - - - - - - - -//

void Map::generateLand()
{
	assert(INITIAL_LAND_TILES <= LAND_TILES);
	placeInitialLandTiles();
	growIslands();
}

void Map::placeInitialLandTiles()
{
	int nbPlacedLandTiles = 0;

	while (nbPlacedLandTiles < INITIAL_LAND_TILES) {
		Coord<int> coord = randTile();
		double distanceWeight = computeDistanceWeight(coord);
		if (nextRand(100) < distanceWeight * 100.0 && !isLand(coord)) {
			setLandTile(coord);
			++nbPlacedLandTiles;
			if (DEBUG_MODE && VERBOSE >= 2 && nbPlacedLandTiles % 1000 == 0) {
				fprintf(stdout, "[%d/%d] tiles placed.\n",
					nbPlacedLandTiles, LAND_TILES);
			}
		}
	}
}

void Map::growIslands()
{
	int nbPlacedLandTiles = INITIAL_LAND_TILES;

	while (nbPlacedLandTiles < LAND_TILES) {
		Coord<int> coord = randTile();
		double distanceWeight = computeDistanceWeight(coord);
		double surroundingLandWeight = computeSurroundingLandWeight(coord);
		double weightedProb = distanceWeight * surroundingLandWeight;

		if (nextRand(100) < weightedProb * 100.0 && !isLand(coord)) {
			setLandTile(coord);
			++nbPlacedLandTiles;
			if (DEBUG_MODE && VERBOSE >= 2 && nbPlacedLandTiles % 1000 == 0) {
				fprintf(stdout, "[%d/%d] tiles placed.\n",
					nbPlacedLandTiles, LAND_TILES);
			}
		}
	}
	if (DEBUG_MODE && VERBOSE >= 2) {
		fprintf(stdout, "[%d/%d] tiles placed.\n",
			nbPlacedLandTiles, LAND_TILES);
	}
}

void Map::setLandTile(Coord<int> coord)
{
	int randomizedHeigth = coord.y + nextRand(-TUNDRA_RANDOMNESS_RADIUS, TUNDRA_RANDOMNESS_RADIUS);

	if (distFromEquatorProportion(randomizedHeigth) > (1 - TUNDRA_PROPORTION)) {
		setEnvironnement(coord, TUNDRA);
	}
	else if (suitablePlainLocation(coord)) {
		setEnvironnement(coord, PLAIN);
	}
	else if (suitableRockyLocation(coord)) {
		setEnvironnement(coord, ROCKY);
	}
	else {
		setEnvironnement(coord, GRASSLAND);
	}
}

bool Map::suitablePlainLocation(Coord<int> coord)
{
	if (placedInitialPlainTiles < INITIAL_PLAIN_TILES) {
		++placedInitialPlainTiles;
		return nextRand(100) < computeAltitudeWeight(coord.y) * 100.0;
	}
	if (hasSurroundingTileOfType(coord, PLAIN)) {
		return nextRand(100) < computeAltitudeWeight(coord.y) * 100.0;
	}
	return false;
}

bool Map::suitableRockyLocation(Coord<int> coord)
{
	if (placedInitialPlainTiles == INITIAL_PLAIN_TILES && 
		placedInitialRockyTiles < INITIAL_ROCKY_TILES) {
		++placedInitialRockyTiles;
		return true;
	}

	int surroundingRockyTiles = countSurroundingTilesOfType(coord, ROCKY);

	if (surroundingRockyTiles > 0 &&
		nextRand(100) < ROCKY_TILES_PROPORTION * 100 &&
		surroundingRockyTiles < ROCKY_ZONE_THICKNESS) {
		return true;
	}
	return false;
}

bool Map::isLand(Coord<int> coord) const
{
	return getTile(coord)->getEnvironnement()->isSolidLand();
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                  DISTANCE                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

double Map::computeDistanceWeight(Coord<int> coord) const
{
	double xMapRadius = MAP_DIMENSIONS.x / 2.0;
	double yMapRadius = MAP_DIMENSIONS.y / 2.0;
	double xWeight = 1 - abs((double)coord.x - xMapRadius) / xMapRadius;
	double yWeight = 1 - abs((double)coord.y - yMapRadius) / yMapRadius;

	return pow(xWeight * yWeight, DISTANCE_CRITERIA_WEIGHT);
}

double Map::computeAltitudeWeight(int y) const
{
	return pow(1 - distFromEquatorProportion(y), PLAIN_ALTITUDE_WEIGHT);
}

double Map::distFromEquatorProportion(int y) const
{
	double distFromEquator = abs((double)y - (double)MAP_DIMENSIONS.y / 2);
	return distFromEquator / ((double)MAP_DIMENSIONS.y / 2);
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//              SURROUNDING TILES              //
//- - - - - - - - - - - - - - - - - - - - - - -//

double Map::computeSurroundingLandWeight(Coord<int> coord) const
{
	int landTiles = countSurroundingLandTiles(coord);
	return pow(((double)landTiles) / 8.0, SURROUNDING_LAND_CRITERIA_WEIGHT);
}

bool Map::hasSurroundingLand(Coord<int> coord) const
{
	return countSurroundingLandTiles(coord) != 0;
}

bool Map::hasSurroundingTileOfType(Coord<int> coord, EnvType type) const
{
	return countSurroundingTilesOfType(coord, type) != 0;
}

int Map::countSurroundingLandTiles(Coord<int> coord) const
{
	int count = 0;
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			if (isLand(Coord<int>(coord.x + x, coord.y + y))) {
				++count;
			}
		}
	}
	return count;
}

int Map::countSurroundingTilesOfType(Coord<int> coord, EnvType type) const
{
	int count = 0;
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			const Tile* tile = getTile(Coord<int>(coord.x + x, coord.y + y));
			if (tile->getEnvironnement()->getType() == type) {
				++count;
			}
		}
	}
	return count;
}