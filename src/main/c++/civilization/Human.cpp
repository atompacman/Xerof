#include "Human.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Human::Human(Position pos): position(pos) 
{
	ready = true;
	moveSpeed = 1;
	rangeOfSight = 2;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   SETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

void Human::setReady()
{
	ready = true;
}

void Human::setBusy()
{
	ready = false;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   GETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

const Tile*** const Human::getSurroundingTiles() const
{
	int zoneSideLength = rangeOfSight * 2 + 1;
	const Tile*** surroundings = new const Tile**[zoneSideLength];
	Map* map = World::getInstance()->map;

	Coord<int> tileCoord;
	Coord<int> delta;

	for (delta.x = 0; delta.x < zoneSideLength; ++delta.x) {
		tileCoord.x = (int)position.coord.x + delta.x - rangeOfSight;
		if (tileCoord.x <= 0 && tileCoord.x >= MAP_DIMENSIONS.x) {
			continue;
		}
		surroundings[delta.x] = new const Tile*[zoneSideLength];

		for (delta.y = 0; delta.y < zoneSideLength; ++delta.y) {
			tileCoord.y = (int)position.coord.y + delta.y - rangeOfSight;
			if (tileCoord.y <= 0 && tileCoord.y >= MAP_DIMENSIONS.y) {
				continue;
			}
			surroundings[delta.x][delta.y] = map->getTile(tileCoord);
		}
	}
	return surroundings;
}

const Tile* const Human::getTileInFront() const
{
	Coord<float> tileCoordF = 
		position.coord.incrementedToDirection(position.facingDirection);
	Coord<int> tileCoord = Coord<int>(tileCoordF.x, tileCoordF.y);
	return World::getInstance()->map->getTile(tileCoord);
}

EnvType Human::getEnvironnementInFront() const
{
	return getTileInFront()->getEnvironment()->getType();
}

bool Human::isReady() const
{
	return ready;
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                    STATS                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

float Human::getMoveSpeed() const
{
	return moveSpeed;
}

unsigned int Human::getRangeOfSight() const
{
	return rangeOfSight;
}