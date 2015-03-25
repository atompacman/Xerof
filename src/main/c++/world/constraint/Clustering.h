#pragma once
#include "..\..\Parameters.h"
#include "Constraint.h"
#include <math.h>

class Clustering : public Constraint
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	Clustering(EnvType i_Type, float i_Compactness) :
        m_Type(i_Type), 
        m_Compactness(i_Compactness) 
    {}

	// WEIGHT
	float getWeightFor(Coord<int> i_Coord) const
	{
		int nbTiles = countSurroundingEnvironOfType(i_Coord, m_Type);
		return pow(((float)nbTiles) / 8.0, m_Compactness);
	}

private:
	EnvType m_Type;
	float   m_Compactness;
};