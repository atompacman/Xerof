#include "Civilization.h"

//= = = = = = = = = = = = = = = = = = = = = = =//
//           CONSTRUCTOR/DESCTRUCTOR           //
//- - - - - - - - - - - - - - - - - - - - - - -//

Civilization::Civilization()
{
	people = new Human*[MAX_POPULATION];
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   GETTERS                   //
//- - - - - - - - - - - - - - - - - - - - - - -//

Human& Civilization::getHuman(unsigned int id) const
{
	assert(id < population);
	return *people[id];
}


//= = = = = = = = = = = = = = = = = = = = = = =//
//                   STATUS                    //
//- - - - - - - - - - - - - - - - - - - - - - -//

unsigned int Civilization::getPopulation() const
{
	return population;
}