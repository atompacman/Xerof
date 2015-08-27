#pragma once

#include <ConstraintWithStrength.h>
#include <JSONUtils.h>

/*============================================================================\\
| A tile has more chance to spawn close or far from the equator
|-----------------------------------------------------------------------------||
| Parameters:
|   - Direction: attaction / repulsion
|   - Strength : how distance affect probabilities
\=============================================================================*/

class DistanceFromEquator : public ConstraintWithStrength
{
public:
    // FACTORY METHOD
    static Constraint* makeAttractionTowardsEquatorConstraint(
        const rapidjson::Value& i_CnstrntElem, const Map& i_Map)
    {
        double strength(parseDouble(i_CnstrntElem, "Strength"));
        return new DistanceFromEquator(i_Map, strength, true);
    }
    static Constraint* makeAttractionTowardsPolesConstraint(
        const rapidjson::Value& i_CnstrntElem, const Map& i_Map)
    {
        double strength(parseDouble(i_CnstrntElem, "Strength"));
        return new DistanceFromEquator(i_Map, strength, false);
    }

    // EVALUATE
    double evaluateLinearConstraint(Biome i_Biome, Coord i_Coord) const
    {
        return abs((double)i_Coord.y - m_Equator) / m_Equator;
    }

private:
    // CONSTRUCTOR/DESTRUCTOR
    DistanceFromEquator(const Map& i_Map,
                        double     i_Strength,
                        bool       i_Attraction) :
        Constraint(i_Map),
        ConstraintWithStrength(i_Map, i_Strength, i_Attraction),
        m_Equator((double)i_Map.height() * 0.5)
    {}

    double m_Equator;
};