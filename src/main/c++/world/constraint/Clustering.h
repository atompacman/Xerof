#pragma once
#include "..\..\Parameters.h"
#include "Constraint.h"
#include <math.h>

class Clustering : public Constraint
{
public:
	// CONSTRUCTOR/DESCTRUCTOR
	Clustering(EnvType type, float compactness) :
		type(type), compactness(compactness) {}

	// WEIGHT
	float getWeightFor(Coord<int> coord) const
	{
		int nbTiles = countSurroundingEnvironOfType(coord, type);
		return pow(((float)nbTiles) / 8.0, compactness);
	}

private:
	EnvType type;
	float compactness;
};