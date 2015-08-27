#pragma once

#include <FatalErrorDialog.h>
#include <JSONUtils.h>
#include <iosfwd>
#include <NearbyElemConstraint.h>

/*============================================================================\\
| Limits the number of surrounding tiles of an environment type to be between
| m_Min and m_Max (binary selection)
|-----------------------------------------------------------------------------||
| Parameters:
|   - The environment type to count
|   - The minimum number of neighbors
|   - The maximum number of neighbors
|   - The manhattan distance to the fartest tile
\=============================================================================*/

class NearbyElemLimits : public NearbyElemConstraint
{
public:
    // FACTORY METHOD
    static Constraint* makeNearbyElemLimitsConstraint(
        const rapidjson::Value& i_CnstrntElem, const Map& i_Map)
    {
        return new NearbyElemLimits(i_Map, 
                                         parseUINT(i_CnstrntElem, "Min"),
                                         parseUINT(i_CnstrntElem, "Max"),
                                         parseUINT(i_CnstrntElem, "Radius"));
    }

    // EVALUATE
    double evaluate(Biome i_Biome, Coord i_Coord) const
    {
        unsigned int neighbouringEnv(countNearbyBiome(i_Biome, i_Coord));
        return neighbouringEnv >= m_Min && neighbouringEnv <= m_Max;
    }

private:

    // CONSTRUCTOR/DESTRUCTOR
    NearbyElemLimits(const Map&   i_Map,
                          unsigned int i_Min,
                          unsigned int i_Max,
                          unsigned int i_Radius) :
        Constraint(i_Map),
        NearbyElemConstraint(i_Map, i_Radius),
        m_Min(i_Min),
        m_Max(i_Max)
    {
        if (i_Min > i_Max) {
            FatalErrorDialog("The minimum num of neighbouring env. \
                              cannot be higher that the maximum");
        }

        unsigned int zoneArea((1 + 2 * i_Radius) * (1 + 2 * i_Radius));
        if (i_Max > zoneArea) {
            std::stringstream ss;
            ss << "Maximum num of neighbouring env. cannot be higher that the "
               << "area of the zone around the center tile (" << zoneArea <<")";
            FatalErrorDialog(ss.str());
        }
    }

    unsigned int m_Min;
    unsigned int m_Max;
};