#include <assert.h>
#include <HumanInfo.h>
#include <Object.h>
#include <Tile.h>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Tile::Tile() :
m_Env(OCEAN),
m_Objs(),
m_Human(NULL)
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   SETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Tile::addObject(Object* i_Obj)
{
    switch (i_Obj->getSize()) {
    case ObjSize::SMALL:
        for (Direction pos = UPPER_RIGHT; pos <= UPPER_LEFT; ++pos) {
            if (!hasObject(pos)) {
                setObject(i_Obj, pos);
            }
        }
        assert(false);
    case ObjSize::MEDIUM:
        for (Direction pos = UP; pos <= LEFT; ++pos) {
            if (!hasObject(pos)) {
                setObject(i_Obj, pos);
            }
        }
        assert(false);
    case ObjSize::BIG:
        setObject(i_Obj, CENTER);
    }
}

void Tile::setObject(Object* i_Obj, Direction i_PosOnTile)
{
    // Check if position on tile is compatible with object size
    switch (i_Obj->getSize()) {
    case ObjSize::SMALL  : assertDiagDir(i_PosOnTile);    break;
    case ObjSize::MEDIUM : assertBasicDir(i_PosOnTile);   break;
    case ObjSize::BIG    : assert(i_PosOnTile == CENTER); break;
    }

    // Place object
    switch (i_PosOnTile) {
    case UP:
        m_Objs[0].setObject(i_Obj);
        m_Objs[1].setObject(i_Obj);
        break;
    case UPPER_RIGHT:
        m_Objs[1].setObject(i_Obj);
        break;    
    case RIGHT:
        m_Objs[1].setObject(i_Obj);
        m_Objs[3].setObject(i_Obj);
        break;
    case LOWER_RIGHT:
        m_Objs[3].setObject(i_Obj);
        break;
    case DOWN:
        m_Objs[2].setObject(i_Obj);
        m_Objs[3].setObject(i_Obj);
        break;
    case LOWER_LEFT:
        m_Objs[2].setObject(i_Obj);
        break;
    case LEFT:
        m_Objs[0].setObject(i_Obj);
        m_Objs[2].setObject(i_Obj);
        break;
    case UPPER_LEFT:
        m_Objs[0].setObject(i_Obj);
        break;
    default:
        m_Objs[0].setObject(i_Obj);
        m_Objs[1].setObject(i_Obj);
        m_Objs[2].setObject(i_Obj);
        m_Objs[3].setObject(i_Obj);
        break;
    }
}

void Tile::setBiome(Biome i_Biome)
{
    m_Env.setBiome(i_Biome);
}

void Tile::setHuman(HumanInfo* i_Human)
{
    m_Human = i_Human;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

const Environment& Tile::getEnvironment() const
{
    return m_Env;
}

std::set<const Object*> Tile::getObjects() const
{
    std::set<const Object*> objs;
    for (unsigned int i = 0; i < 4; ++i) {
        const Object* obj(m_Objs[i].getObject());
        if (obj != NULL) {
            objs.emplace(obj);
        }
    }
    return objs;
}

std::set<const ObjectOnGround*> Tile::getObjectsOnGround() const
{
    std::set<const ObjectOnGround*> objs;
    for (unsigned int i = 0; i < 4; ++i) {
        if (m_Objs[i].getObject() != NULL) {
            objs.emplace(&m_Objs[i]);
        }
    }
    return objs;
}

const HumanInfo* Tile::getHuman() const
{
    return m_Human;
}

HumanInfo* Tile::getHuman()
{
    return m_Human;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    STATUS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Tile::hasObject() const
{
    for (unsigned int i = 0; i < 4; ++i) {
        if (m_Objs[i].getObject() != NULL) {
            return true;
        }
    }
    return false;
}

bool Tile::hasObject(Direction i_PosOnTile) const
{
    switch (i_PosOnTile) {
    case UP:
        return m_Objs[0].getObject() != NULL && 
               m_Objs[1].getObject() != NULL;
    case UPPER_RIGHT:
        return m_Objs[1].getObject() != NULL;
    case RIGHT:
        return m_Objs[1].getObject() != NULL && 
               m_Objs[3].getObject() != NULL;
    case LOWER_RIGHT:
        return m_Objs[3].getObject() != NULL;
    case DOWN:
        return m_Objs[2].getObject() != NULL && 
               m_Objs[3].getObject() != NULL;
    case LOWER_LEFT:
        return m_Objs[2].getObject() != NULL;
    case LEFT:
        return m_Objs[0].getObject() != NULL && 
               m_Objs[2].getObject() != NULL;
    case UPPER_LEFT:
        return m_Objs[0].getObject() != NULL;
    default:
        return hasObject();
    }
}

bool Tile::hasHuman() const
{
    return m_Human != NULL;
}

bool Tile::isPassable() const
{
    if (!m_Env.isSolidLand()) {
        return false;
    }
    for (unsigned int i = 0; i < 4; ++i) {
        const Object* obj(m_Objs[i].getObject());
        if (obj != NULL && !obj->isPassable()) {
            return false;
        }
    }
    return m_Human == NULL;
}
