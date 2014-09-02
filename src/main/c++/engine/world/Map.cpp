#include "Map.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Map::Map()
{
	assert(INITIAL_LAND_TILES < LAND_TILES);
	assert(TUNDRA_PROPORTION < 1.0);
	assert(TUNDRA_RANDOMNESS_RADIUS < MAP_HEIGHT / 2);
	placedInitialPlainTiles = 0;
	placedInitialRockyTiles = 0;

	initWorldGeneratorSeed();
	fillWithOcean();
	generateLand();
	detectLakeBorders();
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   SETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

void Map::setEnvironnement(unsigned int x, unsigned int y, Background* back)
{
	assert(x < MAP_LENGTH);
	assert(y < MAP_HEIGHT);

	tiles[x][y].setBackground(back);
}

void Map::setContent(unsigned int x, unsigned int y, Foreground* front)
{
	assert(x < MAP_LENGTH);
	assert(y < MAP_HEIGHT);

	tiles[x][y].setForeground(front);
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   GETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

const Tile& Map::getTile(unsigned int x, unsigned int y) const
{
	assert(x < MAP_LENGTH);
	assert(y < MAP_HEIGHT);
	return tiles[x][y];
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//               MAP GENERATION                //
//- - - - - - - - - - - - - - - - - - - - - - -//

void Map::fillWithOcean()
{
	for (int y = 0; y < MAP_HEIGHT; ++y) {
		for (int x = 0; x < MAP_LENGTH; ++x) {
			tiles[x][y].setBackground(new Ocean());
		}
	}
}

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
			if (nbPlacedLandTiles % 100 == 0) {
				std::cout << '[' << nbPlacedLandTiles << "/" << LAND_TILES
					<< "] tiles placed." << std::endl;
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
			if (nbPlacedLandTiles % 100 == 0) {
				std::cout << '[' << nbPlacedLandTiles << "/" << LAND_TILES
					<< "] tiles placed." << std::endl;
			}
		}
	}
}

void Map::setLandTile(const RandCoord& coord)
{
	int randomizedHeigth = coord.y + nextRand(-TUNDRA_RANDOMNESS_RADIUS, TUNDRA_RANDOMNESS_RADIUS);

	if (distFromEquatorProportion(randomizedHeigth) > (1 - TUNDRA_PROPORTION)) {
		setEnvironnement(coord.x, coord.y, new Tundra());
	}
	else if (suitablePlainLocation(coord)) {
		setEnvironnement(coord.x, coord.y, new Plain());
	}
	else if (suitableRockyLocation(coord)) {
		setEnvironnement(coord.x, coord.y, new Rocky());
	}
	else {
		setEnvironnement(coord.x, coord.y, new Grassland());
	}
}

bool Map::suitablePlainLocation(const RandCoord& coord)
{
	if (placedInitialPlainTiles < INITIAL_PLAIN_TILES) {
		++placedInitialPlainTiles;
		return nextRand(100) < computeAltitudeWeight(coord.y) * 100.0;
	}
	if (hasSurroundingPlain(coord)) {
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
	if (countSurroundingRockyTiles(coord) > 0 &&
		nextRand(100) < ROCKY_TILES_PROPORTION * 100 &&
		countSurroundingRockyTiles(coord) < ROCKY_ZONE_THICKNESS) {
		return true;
	}
	return false;
}

bool Map::isLand(unsigned int x, unsigned int y) const
{
	return getTile(x, y).getBackground()->isSolidLand();
}

void Map::detectLakeBorders()
{
	for (int y = 1; y < MAP_HEIGHT - 1; ++y) {
		for (int x = 1; x < MAP_LENGTH - 1; ++x) {
			if (isLand(x, y)) {
				continue;
			}

		}
	}
}

bool Map::canReachLimitsFrom() const
{

}

//= = = = = = = = = = = = = = = = = = = = = = =//
//                  DISTANCE                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

double Map::computeDistanceWeight(const RandCoord& coord) const
{
	double xMapRadius = MAP_LENGTH / 2.0;
	double yMapRadius = MAP_HEIGHT / 2.0;
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
	double distFromEquator = abs((double)y - (double)MAP_HEIGHT / 2);
	return distFromEquator / ((double)MAP_HEIGHT / 2);
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//              SURROUNDING TILES              //
//- - - - - - - - - - - - - - - - - - - - - - -//

double Map::computeSurroundingLandWeight(const RandCoord& coord) const
{
	int landTiles = countSurroundingLandTiles(coord);
	return pow(((double)landTiles) / 8.0, SURROUNDING_LAND_CRITERIA_WEIGHT);
}

double Map::hasSurroundingLand(const RandCoord& coord) const
{
	return countSurroundingLandTiles(coord) != 0;
}

double Map::hasSurroundingPlain(const RandCoord& coord) const
{
	return countSurroundingPlainTiles(coord) != 0;

}

int Map::countSurroundingLandTiles(const RandCoord& coord) const
{
	int landTiles = 0;
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			if (isLand(coord.x + x, coord.y + y)) {
				++landTiles;
			}
		}
	}
	return landTiles;
}

int Map::countSurroundingPlainTiles(const RandCoord& coord) const
{
	int plain = 0;
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			const Background* back = getTile(coord.x + x, coord.y + y).getBackground();
			if (typeid(*back) == typeid(const Plain)) {
				++plain;
			}
		}
	}
	return plain;
}

int Map::countSurroundingRockyTiles(const RandCoord& coord) const
{
	int rocky = 0;
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			const Background* back = getTile(coord.x + x, coord.y + y).getBackground();
			if (typeid(*back) == typeid(const Rocky)) {
				++rocky;
			}
		}
	}
	return rocky;
}