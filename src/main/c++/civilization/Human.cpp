#include "Human.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Human::Human(Position i_Pos): 
m_Pos(i_Pos),
m_IsReady(true),
m_MoveSpeed(1),
m_ROSight(2)
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   SETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Human::setReady()
{
	m_IsReady = true;
}

void Human::setBusy()
{
	m_IsReady = false;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Tile*** const Human::getSurroundingTiles() const
{
	int zoneSideLength = m_ROSight * 2 + 1;
	const Tile*** surroundings = new const Tile**[zoneSideLength];
	Map* map = World::getInstance()->map;

	Coord<int> tileCoord;
	Coord<int> delta;

	for (delta.x = 0; delta.x < zoneSideLength; ++delta.x) {
		tileCoord.x = (int)m_Pos.coord.x + delta.x - m_ROSight;
		if (tileCoord.x <= 0 && tileCoord.x >= MAP_DIMENSIONS.x) {
			continue;
		}
		surroundings[delta.x] = new const Tile*[zoneSideLength];

		for (delta.y = 0; delta.y < zoneSideLength; ++delta.y) {
			tileCoord.y = (int)m_Pos.coord.y + delta.y - m_ROSight;
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
		m_Pos.coord.incrementedToDirection(m_Pos.facingDirection);
	Coord<int> tileCoord = Coord<int>(tileCoordF.x, tileCoordF.y);
	return World::getInstance()->map->getTile(tileCoord);
}

EnvType Human::getEnvironnementInFront() const
{
	return getTileInFront()->getEnvironment()->getType();
}

bool Human::isReady() const
{
	return m_IsReady;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                     STATS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

float Human::getMoveSpeed() const
{
	return m_MoveSpeed;
}

unsigned int Human::getRangeOfSight() const
{
	return m_ROSight;
}