#pragma once
// new behavior: elements of array 'm_Objs' will be default initialized
#pragma warning(disable : 4351)

#include <Environment.h>
#include <ObjectOnGround.h>
#include <set>

/*============================================================================\\
| A tile on the map
|-----------------------------------------------------------------------------||
| A tile has an environment and up to 4 objects
\=============================================================================*/

class HumanInfo;
class Object;

class Tile
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    Tile();

    // SETTERS
    void addObject(Object* i_Obj);
    void setObject(Object* i_Obj, Direction i_PosOnTile);
    void setBiome(Biome i_Biome);
    void setHuman(HumanInfo* i_Human);

    // GETTERS
    const Environment&              getEnvironment()     const;
    std::set<const Object*>         getObjects()         const;
    std::set<const ObjectOnGround*> getObjectsOnGround() const;
    const HumanInfo*                getHuman()           const;
    HumanInfo*                      getHuman();

    // STATUS
    bool hasObject()                      const;
    bool hasObject(Direction i_PosOnTile) const;
    bool hasHuman()                       const;
    bool isPassable()                     const;

private:
    Environment    m_Env;
    ObjectOnGround m_Objs[4];
    HumanInfo*     m_Human;
};