#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Environment.h"
/*============================================================================||
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
    ~Tile();

    // SETTERS
    void setObject(Direction i_Dir, Object* i_Obj);
    void setEnvironment(Biome i_Type);
    void setHuman(HumanInfo* i_Human);

    // REMOVE
    void removeObject(Direction i_Dir);

    // GETTERS
    const Environment& getEnvironment() const;
    Object*            getObject(Direction i_Dir) const;
    const HumanInfo*   getHuman() const;
    HumanInfo*         getHuman();

    // HAS
    bool hasObject(Direction i_Dir) const;
    bool hasObject() const;
    bool hasHuman() const;

    // STATUS
    bool isPassable() const;

private:
    Environment m_Env;
    Object**    m_Objs;
    HumanInfo*  m_Human;
};