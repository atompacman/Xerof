#pragma once

#include <ConstraintWithStrength.h>
#include <JSONUtils.h>

/*============================================================================\\
| A tile has more chance to spawn close or far from center of the map
|-----------------------------------------------------------------------------||
| Parameters:
|   - Direction: attaction / repulsion
|   - Strength : how distance affect probabilities
\=============================================================================*/

static const double SQRT2 = 1.41421356237309504880;

class DistanceFromCenter : public ConstraintWithStrength
{
public:
    // FACTORY METHOD
    static Constraint* makeAttractionTowardsCenterConstraint(
        const rapidjson::Value& i_CnstrntElem, const Map& i_Map)
    {
        double strength(parseDouble(i_CnstrntElem, "Strength"));
        return new DistanceFromCenter(i_Map, strength, true);
    }
    static Constraint* makeRepulsionFromCenterConstraint(
        const rapidjson::Value& i_CnstrntElem, const Map& i_Map)
    {
        double strength(parseDouble(i_CnstrntElem, "Strength"));
        return new DistanceFromCenter(i_Map, strength, false);
    }

    // EVALUATE
    double evaluateLinearConstraint(Biome i_Biome, Coord i_Coord) const
    {
        double distX(fabs((double)i_Coord.x - m_MapCenter.x) / m_ConvFactor.x);
        double distY(fabs((double)i_Coord.y - m_MapCenter.y) / m_ConvFactor.y);
        return sqrt(distX * distX + distY * distY);
    }

private:
    // CONSTRUCTOR/DESTRUCTOR
    DistanceFromCenter(const Map& i_Map,
                       double     i_Strength,
                       bool       i_Attraction) :
        Constraint(i_Map),
        ConstraintWithStrength(i_Map, i_Strength, i_Attraction),
        m_MapCenter(toDCoord(m_Map.dimensions()) * 0.5),
        m_ConvFactor(m_MapCenter * SQRT2)
    {}

    DCoord m_MapCenter;
    DCoord m_ConvFactor;
};
