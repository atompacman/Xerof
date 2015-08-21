#pragma once

#include <Direction.h>

/*============================================================================\\
| The layer between tiles and actual objects
|-----------------------------------------------------------------------------||
| Objects are disposed on the ground in a certain way. In the future, 
| information like the time the object was dropped on the ground can be stored
| here.
\=============================================================================*/

class Object;

class ObjectOnGround
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    ObjectOnGround() :
        m_Obj(NULL),
        m_Disposition()
    {}

    // SETTERS
    void setObject(Object* i_Obj)
    {
        assert(m_Obj == NULL);
        m_Obj = i_Obj;
        m_Disposition = Disposition();
    }

    // GETTERS
    Object* getObject()
    {
        return m_Obj;
    }
    const Object* getObject() const
    {
        return m_Obj;
    }
    Disposition getDisposition() const
    {
        return m_Disposition;
    }

    // OPERATOR
    bool operator<(const ObjectOnGround& i_Other) 
    {
        return m_Obj < i_Other.m_Obj;
    }

private:
    Object*     m_Obj;
    Disposition m_Disposition;
};
