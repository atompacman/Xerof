#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "NeighbouringEnvConstraint.h"
/*============================================================================//
| Limits the number of surrounding tiles of an environment type to be between
| m_Min and m_Max (binary selection)
|-----------------------------------------------------------------------------||
| Parameters:
|   - The environment type to count
|   - The minimum number of neighbors
|   - The maximum number of neighbors
|   - The manhattan distance to the fartest tile
\=============================================================================*/

class NeighbouringEnvLimits : public NeighbouringEnvConstraint
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    NeighbouringEnvLimits(const Map& i_Map,
                          Biome      i_EnvType,
                          UINT       i_Min,
                          UINT       i_Max,
                          UINT       i_Radius) :
        Constraint(i_Map),
        NeighbouringEnvConstraint(i_Map, i_EnvType, i_Radius),
        m_Min(i_Min),
        m_Max(i_Max)
    {
        if (i_Min > i_Max) {
            FatalErrorDialog("The minimum num of neighbouring env. \
                               cannot be higher that the maximum");
        }

        UINT zoneArea((1 + 2 * i_Radius) * (1 + 2 * i_Radius));
        if (i_Max > zoneArea) {
            std::stringstream ss;
            ss << "Maximum num of neighbouring env. cannot be higher that the "
                << "area of the zone around the center tile ("<< zoneArea <<")";
            FatalErrorDialog(ss.str());
        }
    }

    // WEIGHT
    double getWeightFor(Coord i_Coord) const
    {
        UINT neighbouringEnv(countNeighbourEnv(i_Coord));
        return neighbouringEnv >= m_Min && neighbouringEnv <= m_Max;
    }

private:
    UINT m_Min;
    UINT m_Max;
};