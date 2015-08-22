#pragma once

#include <Individual.h>
#include <vector>

/*============================================================================\\
| A group of humans
|-----------------------------------------------------------------------------||
| For now, a civ is not bigger than the sum of its parts...
\=============================================================================*/

class Civilization
{
    friend class CivController;

public:
    // CONSTRUCTOR/DESTRUCTOR
    Civilization();

    // GETTERS
    const Individual& getIndividual(unsigned int i_ID) const;
    Individual&       getIndividual(unsigned int i_ID);

    // STATUS
    unsigned int population() const;

private:
    std::vector<Individual> m_People;
};