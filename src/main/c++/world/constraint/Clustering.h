#pragma once
#include <math.h>
#include "Constraint.h"

class Clustering : public Constraint
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Clustering(const Map2& i_Map, EnvType i_Type, float i_Compactness) :
        Constraint(i_Map),
        m_Type(i_Type),
        m_Compactness(i_Compactness)
    {}

    // WEIGHT
    float getWeightFor(Coord i_Coord) const
    {
        int nbTiles = countSurroundingEnvironOfType(i_Coord, m_Type);
        return pow(((float)nbTiles) / 8.0, m_Compactness);
    }

private:
    EnvType m_Type;
    float   m_Compactness;
};