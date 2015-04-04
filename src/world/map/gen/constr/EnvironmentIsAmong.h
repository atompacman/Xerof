#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <set>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Constraint.h"
/*============================================================================||
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
    void addEnv(EnvType i_EnvType)
    {
        m_EnvTypes.insert(i_EnvType);
    }

	// WEIGHT
    double getWeightFor(Coord i_Coord) const
	{
        EnvType currEnv(m_Map.getTile(i_Coord).getEnvironment().getType());
        return m_EnvTypes.find(currEnv) != m_EnvTypes.end();
	}

private:
    std::set<EnvType> m_EnvTypes;
};