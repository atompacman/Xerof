#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Constraint.h"
#include "..\src\utils\Elem2D.h"
#include "..\..\Map.h"
/*============================================================================//
| Clustering
|-----------------------------------------------------------------------------||
| Todo
\=============================================================================*/

class Clustering : public Constraint
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Clustering(const Map& i_Map, EnvType i_Type, double i_Compactness) :
        Constraint(i_Map),
        m_Type(i_Type),
        m_Compactness(i_Compactness)
    {}

    // WEIGHT
    double getWeightFor(Coord i_Coord) const
    {
        UINT nbTiles = countSurroundingEnvironOfType(i_Coord, m_Type);
        return pow(((double)nbTiles) / 8.0, m_Compactness);
    }

private:
    EnvType m_Type;
    double  m_Compactness;
};