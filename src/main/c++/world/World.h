#pragma once
#include <assert.h>
#include "Map.h"
#include "MapGenerator.h"

class World
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    World(const MapConfig& i_MapConfig);

    // GETTERS
    const Map& map() const;

private:
    Map m_Map;
};
