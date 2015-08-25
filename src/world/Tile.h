#pragma once
// new behavior: elements of array 'm_Objs' will be default initialized
#pragma warning(disable : 4351)

#include <Environment.h>
#include <set>

/*============================================================================\\
| A tile on the map
|-----------------------------------------------------------------------------||
| A tile has an environment and up to 4 objects
\=============================================================================*/

class Individual;
class Object;

class Tile
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Tile();

    // SETTERS
    void addObject(Object* i_Obj);
    bool tryToAddObject(Object* i_Obj);
    void setObject(Object* i_Obj, Direction i_PosOnTile);
    void setBiome(Biome i_Biome);
    void setIndividual(Individual* i_Human);

    // GETTERS
    const Environment&      getEnvironment() const;
    std::set<const Object*> getObjects()     const;
    const Individual*       getIndividual()  const;
    Individual*             getIndividual();

    // STATUS
    bool hasObject()                      const;
    bool hasObject(Direction i_PosOnTile) const;
    bool hasPlaceFor(Object* i_Obj)       const;
    bool hasIndividual()                  const;
    bool isPassable()                     const;

private:
    Environment m_Env;
    Object*     m_Objs[4];
    Individual* m_Individual;
};