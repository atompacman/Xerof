#pragma once

#include <Constraint.h>
#include <set>

/*============================================================================\\
| Environment to replace must be in a list of environment
|-----------------------------------------------------------------------------||
| Simple isn't it ?
\=============================================================================*/

class EnvironmentIsAmong : public Constraint
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    EnvironmentIsAmong(const Map& i_Map) :
        Constraint(i_Map),
        m_EnvTypes()
    {}

    // ADD
    void addEnv(Biome i_EnvType)
    {
        m_EnvTypes.insert(i_EnvType);
    }

    // WEIGHT
    double getWeightFor(Coord i_Coord) const
    {
        Biome currEnv(m_Map(i_Coord).getEnvironment().getBiome());
        return m_EnvTypes.find(currEnv) != m_EnvTypes.end();
    }

private:
    std::set<Biome> m_EnvTypes;
};