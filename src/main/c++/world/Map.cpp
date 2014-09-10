#include "Map.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Map::Map()
{
	tiles = new Tile*[MAP_WIDTH_IN_TILES * MAP_HEIGHT_IN_TILES];

	int tileNo = 0;

	for (int y = 0; y < MAP_HEIGHT_IN_TILES; ++y) {
		for (int x = 0; x < MAP_WIDTH_IN_TILES; ++x) {
			Tile * tile = new Tile();
			tile->setEnvironnement(OCEAN);
			tiles[x + y * MAP_WIDTH_IN_TILES] = tile;
			++tileNo;
			if (DEBUG_MODE && VERBOSE >= 2 && tileNo % 1000 == 0) {
				fprintf(stdout, "[%d/%d] tiles allocated in memory.\n",
					tileNo, TOTAL_NB_TILES);
			}
		}
	}

	assert(INITIAL_LAND_TILES < LAND_TILES);
	assert(TUNDRA_PROPORTION < 1.0);
	assert(TUNDRA_RANDOMNESS_RADIUS < MAP_HEIGHT_IN_TILES / 2);
	placedInitialPlainTiles = 0;
	placedInitialRockyTiles = 0;

	initWorldGeneratorSeed();
	generateLand();
}

Map::~Map()
{
	for (int y = 0; y < MAP_HEIGHT_IN_TILES; ++y) {
		for (int x = 0; x < MAP_WIDTH_IN_TILES; ++x) {
			delete getTile(x, y);
		}
	}
	delete[] tiles;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   SETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

void Map::setEnvironnement(unsigned int x, unsigned int y, EnvType type)
{
	assert(x < MAP_WIDTH_IN_TILES);
	assert(y < MAP_HEIGHT_IN_TILES);

	getTile(x, y)->setEnvironnement(type);
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   GETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

Tile* Map::getTile(unsigned int x, unsigned int y) const
{
	assert(x < MAP_WIDTH_IN_TILES);
	assert(y < MAP_HEIGHT_IN_TILES);
	return tiles[x + y * MAP_WIDTH_IN_TILES];
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
		RandCoord coord;
		double distanceWeight = computeDistanceWeight(coord);
		if (nextRand(100) < distanceWeight * 100.0 && !isLand(coord.x, coord.y)) {
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
		RandCoord coord;
		double distanceWeight = computeDistanceWeight(coord);
		double surroundingLandWeight = computeSurroundingLandWeight(coord);
		double weightedProb = distanceWeight * surroundingLandWeight;

		if (nextRand(100) < weightedProb * 100.0 && !isLand(coord.x, coord.y)) {
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

void Map::setLandTile(const RandCoord& coord)
{
	int randomizedHeigth = coord.y + nextRand(-TUNDRA_RANDOMNESS_RADIUS, TUNDRA_RANDOMNESS_RADIUS);

	if (distFromEquatorProportion(randomizedHeigth) > (1 - TUNDRA_PROPORTION)) {
		setEnvironnement(coord.x, coord.y, TUNDRA);
	}
	else if (suitablePlainLocation(coord)) {
		setEnvironnement(coord.x, coord.y, PLAIN);
	}
	else if (suitableRockyLocation(coord)) {
		setEnvironnement(coord.x, coord.y, ROCKY);
	}
	else {
		setEnvironnement(coord.x, coord.y, GRASSLAND);
	}
}

bool Map::suitablePlainLocation(const RandCoord& coord)
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

bool Map::suitableRockyLocation(const RandCoord& coord)
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

bool Map::isLand(unsigned int x, unsigned int y) const
{
	return getTile(x, y)->getEnvironnement()->isSolidLand();
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                  DISTANCE                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

double Map::computeDistanceWeight(const RandCoord& coord) const
{
	double xMapRadius = MAP_WIDTH_IN_TILES / 2.0;
	double yMapRadius = MAP_HEIGHT_IN_TILES / 2.0;
	double xWeight = 1 - abs((double)coord.x - xMapRadius) / xMapRadius;
	double yWeight = 1 - abs((double)coord.y - yMapRadius) / yMapRadius;

	return pow(xWeight * yWeight, DISTANCE_CRITERIA_WEIGHT);
}

double Map::computeAltitudeWeight(unsigned int y) const
{
	return pow(1 - distFromEquatorProportion(y), PLAIN_ALTITUDE_WEIGHT);
}

double Map::distFromEquatorProportion(unsigned int y) const
{
	double distFromEquator = abs((double)y - (double)MAP_HEIGHT_IN_TILES / 2);
	return distFromEquator / ((double)MAP_HEIGHT_IN_TILES / 2);
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//              SURROUNDING TILES              //
//- - - - - - - - - - - - - - - - - - - - - - -//

double Map::computeSurroundingLandWeight(const RandCoord& coord) const
{
	int landTiles = countSurroundingLandTiles(coord);
	return pow(((double)landTiles) / 8.0, SURROUNDING_LAND_CRITERIA_WEIGHT);
}

bool Map::hasSurroundingLand(const RandCoord& coord) const
{
	return countSurroundingLandTiles(coord) != 0;
}

bool Map::hasSurroundingTileOfType(const RandCoord& coord, EnvType type) const
{
	return countSurroundingTilesOfType(coord, type) != 0;
}

int Map::countSurroundingLandTiles(const RandCoord& coord) const
{
	int count = 0;
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			if (isLand(coord.x + x, coord.y + y)) {
				++count;
			}
		}
	}
	return count;
}

int Map::countSurroundingTilesOfType(const RandCoord& coord, EnvType type) const
{
	int count = 0;
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			const Tile* tile = getTile(coord.x + x, coord.y + y);
			if (tile->getEnvironnement()->getType() == type) {
				++count;
			}
		}
	}
	return count;
}