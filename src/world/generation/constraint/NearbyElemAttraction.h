#pragma once

#include <ConstraintWithStrength.h>
#include <JSONUtils.h>
#include <NearbyElemConstraint.h>

/*============================================================================\\
| The more a spot is surrounded by the same environment, the more probably the
| env. placement will be.
|-----------------------------------------------------------------------------||
| Parameters:
|   - The environment type to count
|   - The manhattan distance to the fartest 
|   - Strength : how critical is the effect of this constraint
\=============================================================================*/

class NearbyElemAttraction : public NearbyElemConstraint,
                             public ConstraintWithStrength 
{
public:
    // FACTORY METHOD
    static Constraint* makeNearbyElemAttractionConstraint(
        const rapidjson::Value& i_CnstrntElem, const Map& i_Map)
    {
        return new NearbyElemAttraction(
                                    i_Map,
                                    parseUINT(i_CnstrntElem, "Radius"),
                                    parseDouble(i_CnstrntElem, "Strength"));
    }

    // EVALUATE
    double evaluate(Biome i_Biome, Coord i_Coord) const
    {
        return ConstraintWithStrength::evaluate(i_Biome, i_Coord);
    }
    double evaluateLinearConstraint(Biome i_Biome, Coord i_Coord) const
    {
        unsigned int neighbouringBiome(countNearbyBiome(i_Biome,i_Coord));
        return (double) neighbouringBiome / (double)(m_Radius * m_Radius);
    }

private:
    // CONSTRUCTOR/DESTRUCTOR
    NearbyElemAttraction(const Map&   i_Map,
                              unsigned int i_Radius,
                              double       i_Strength) :
        Constraint(i_Map),
        NearbyElemConstraint(i_Map, i_Radius),
        ConstraintWithStrength(i_Map, i_Strength, false)
    {}
};
