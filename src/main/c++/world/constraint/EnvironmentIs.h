#pragma once
#include "Constraint.h"

class EnvironmentIs: public Constraint
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    EnvironmentIs(const Map& i_Map, EnvType i_Type) :
        Constraint(i_Map),
        m_Type(i_Type) 
    {}

	// WEIGHT
    double getWeightFor(Coord m_Coord) const
	{
		return m_Map.getTile(m_Coord).getEnvironment().getType() == m_Type;
	}

private:
	EnvType m_Type;
};