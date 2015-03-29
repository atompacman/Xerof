#pragma once
#include "..\..\civilization\Human.h"
#include "Process.h"

class HumanProcess : public Process
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    HumanProcess(Human* i_Human) :
        m_Human(*i_Human)
    {}

	// NEXT ITERATION
	virtual void nextIter() = 0;

protected:
    Human& m_Human;
};