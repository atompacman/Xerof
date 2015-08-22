#include <assert.h>
#include <Individual.h>
#include <Object.h>
#include <Tile.h>

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Tile::Tile() :
m_Env(OCEAN),
m_Objs(),
m_Individual(NULL)
{}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   SETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

void Tile::addObject(Object* i_Obj)
{
    assert(tryToAddObject(i_Obj));
}

bool Tile::tryToAddObject(Object* i_Obj)
{
    switch (i_Obj->getSize()) {
    case ObjSize::SMALL:
        for (Direction pos = UPPER_RIGHT; pos <= UPPER_LEFT; ++pos) {
            if (!hasObject(pos)) {
                setObject(i_Obj, pos);
                return true;
            }
        }
        return false;
    case ObjSize::MEDIUM:
        for (Direction pos = UP; pos <= LEFT; ++pos) {
            if (!hasObject(pos)) {
                setObject(i_Obj, pos);
                return true;
            }
        }
        return false;
    default:
        if (!hasObject()) {
            setObject(i_Obj, CENTER);
            return true;
        }
        return false;
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
    case UP:          m_Objs[0] = m_Objs[1] = i_Obj; break;
    case UPPER_RIGHT: m_Objs[1]             = i_Obj; break;    
    case RIGHT:       m_Objs[1] = m_Objs[3] = i_Obj; break;
    case LOWER_RIGHT: m_Objs[3]             = i_Obj; break;
    case DOWN:        m_Objs[2] = m_Objs[3] = i_Obj; break;
    case LOWER_LEFT:  m_Objs[2]             = i_Obj; break;
    case LEFT:        m_Objs[0] = m_Objs[2] = i_Obj; break;
    case UPPER_LEFT:  m_Objs[0]             = i_Obj; break;
    default:          m_Objs[0] = m_Objs[1] = 
                      m_Objs[2] = m_Objs[3] = i_Obj; break;
    }
}

void Tile::setBiome(Biome i_Biome)
{
    m_Env.setBiome(i_Biome);
}

void Tile::setIndividual(Individual* i_Individual)
{
    m_Individual = i_Individual;
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
        if (m_Objs[i] != NULL) {
            objs.emplace(m_Objs[i]);
        }
    }
    return objs;
}

const Individual* Tile::getIndividual() const
{
    return m_Individual;
}

Individual* Tile::getIndividual()
{
    return m_Individual;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                    STATUS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

bool Tile::hasObject() const
{
    for (unsigned int i = 0; i < 4; ++i) {
        if (m_Objs[i] != NULL) {
            return true;
        }
    }
    return false;
}

bool Tile::hasObject(Direction i_PosOnTile) const
{
    switch (i_PosOnTile) {
    case UP:          return m_Objs[0] != NULL && m_Objs[1] != NULL;
    case UPPER_RIGHT: return m_Objs[1] != NULL;
    case RIGHT:       return m_Objs[1] != NULL && m_Objs[3] != NULL;
    case LOWER_RIGHT: return m_Objs[3] != NULL;
    case DOWN:        return m_Objs[2] != NULL && m_Objs[3] != NULL;
    case LOWER_LEFT:  return m_Objs[2] != NULL;
    case LEFT:        return m_Objs[0] != NULL && m_Objs[2] != NULL;
    case UPPER_LEFT:  return m_Objs[0] != NULL;
    default:          return hasObject();
    }
}

bool Tile::hasPlaceFor(Object* i_Obj) const
{
    switch (i_Obj->getSize()) {
    case ObjSize::SMALL:
        for (Direction pos = UPPER_RIGHT; pos <= UPPER_LEFT; ++pos) {
            if (!hasObject(pos)) {
                return true;
            }
        }
        return false;
    case ObjSize::MEDIUM:
        for (Direction pos = UP; pos <= LEFT; ++pos) {
            if (!hasObject(pos)) {
                return true;
            }
        }
        return false;
    default:
        return hasObject();
    }
}

bool Tile::hasIndividual() const
{
    return m_Individual != NULL;
}

bool Tile::isPassable() const
{
    if (!m_Env.isSolidLand()) {
        return false;
    }
    for (unsigned int i = 0; i < 4; ++i) {
        if (m_Objs[i] != NULL && !m_Objs[i]->isPassable()) {
            return false;
        }
    }
    return m_Individual == NULL;
}
