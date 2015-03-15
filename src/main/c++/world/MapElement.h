#pragma once
#include "..\assets\Assets.h"

enum MapElemType
{
	ENVIRONNEMENT, OBJECT
};


class MapElement
{
public:
	// ASSET
	virtual Asset assetFile() const = 0;
};