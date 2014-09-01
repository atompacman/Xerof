#include "Map.h"


//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Map::Map()
{
	initWorldGeneratorSeed();
	fillWithOcean();
	generateLand();
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
			setEnvironnement(coord.x, coord.y, new Grassland());
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
			setEnvironnement(coord.x, coord.y, new Grassland());
			++nbPlacedLandTiles;
			if (nbPlacedLandTiles % 100 == 0) {
				std::cout << '[' << nbPlacedLandTiles << "/" << LAND_TILES
					<< "] tiles placed." << std::endl;
			}
			//if (suitableForAForest(coord.x, coord.y)) {
			//	  setContent(coord.x, coord.y, new TemperateForest());
			//}
		}
	}
}

bool Map::suitableForAForest(unsigned int x, unsigned int y) const
{
	//TODO
	return true;
}

double Map::computeDistanceWeight(const RandCoord& coord) const
{
	double xMapRadius = MAP_LENGTH / 2.0;
	double yMapRadius = MAP_HEIGHT / 2.0;
	double xWeight = 1 - abs((double)coord.x - xMapRadius) / xMapRadius;
	double yWeight = 1 - abs((double)coord.y - yMapRadius) / yMapRadius;

	return pow(xWeight * yWeight, DISTANCE_CRITERIA_WEIGHT);
}

double Map::computeSurroundingLandWeight(const RandCoord& coord) const
{
	int landTiles = 0;
	for (int y = -1; y <= 1; ++y) {
		for (int x = -1; x <= 1; ++x) {
			if (isLand(coord.x + x, coord.y + y)) {
				++landTiles;
			}
		}
	}
	return pow(((double)landTiles) / 8.0, SURROUNDING_LAND_CRITERIA_WEIGHT);
}

bool Map::isLand(unsigned int x, unsigned int y) const
{
	return getTile(x, y).getBackground()->isSolidLand();
}