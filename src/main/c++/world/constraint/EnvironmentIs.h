#pragma once
#include "..\Map2.h"
#include "Constraint.h"

class EnvironmentIs : public Constraint
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    EnvironmentIs(EnvType i_Type) : 
        m_Type(i_Type) 
    {}

	// WEIGHT
	float getWeightFor(Coord<int> m_Coord) const
	{
		return s_Map->getTile(m_Coord)->getEnvironment()->getType() == m_Type;
	}

private:
	EnvType m_Type;
};