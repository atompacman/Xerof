#pragma once
#include "..\assets\Assets.h"

class MapElement
{
public:
	// ASSET
	virtual Asset assetFile() const = 0;
};