#include <iostream>
#include "Object.h"

Object::Object()
{
    m_nameObject = "no object";
    m_type = other;
    m_index = 500;
    m_pos = nullptr;
    m_isLooted = false;
    m_isDestroyed = true;
    m_isDropped=false;
    m_value = 0;
}

Object::Object(const std::string &name, ObjectType type, unsigned int index,
               const Rectangle &pos, int value, bool looted, bool dropped)
{
    m_nameObject = name;
    m_type = type;
    m_index = index;
    m_pos = new Rectangle(pos);
    m_value = value;
    m_isLooted = looted;
    m_isDestroyed = false;
    m_isDropped = dropped;
}

/*Object::Object(const Object &copie)
{
    m_nameObject = copie.m_nameObject;
    m_type = copie.m_type;
    m_index = copie.m_index;
    m_pos = new Rectangle(*(copie.m_pos));
    m_value = copie.m_value;
    m_isLooted = copie.m_isLooted;
    m_isDestroyed = copie.m_isDestroyed;
    m_isDropped = copie.m_isDropped;
}
*/
Object::~Object()
{
    delete m_pos;
    m_pos = nullptr;
}

std::string Object::getNameObject() const
{
    return m_nameObject;
}

ObjectType Object::getType() const
{
    return m_type;
}

unsigned int Object::getIndex() const
{
    return m_index;
}

Rectangle &Object::getPos() const
{
    return *m_pos;
}

bool Object::isLooted() const
{
    return m_isLooted;
}

int Object::getValue() const
{
    return m_value;
}

bool Object::isDestroyed() const
{
    return m_isDestroyed;
}

bool Object::isDropped() const
{
    return m_isDropped;
}

void Object::setLooted(bool looted)
{
    m_isLooted = looted;
}

void Object::setDropped(bool dropped)
{
    m_isDropped = dropped;
}

void Object::setPos(const Rectangle &pos)
{
    delete m_pos;
    m_pos = new Rectangle(pos);
}

void Object::setIndex(unsigned int index)
{
    m_index = index;
}

std::string Object::getObjectType() const
{
    switch(m_type)
    {
    case 0:
        return "Weapon";
    case 1:
        return "Armor";
    case 2:
        return "Other";
    default:
        return "error";
    }
}

void Object::setNameObject(const std::string &name)
{
    m_nameObject = name;
}

Object &Object::operator=(const Object &copie)
{
    if(this != &copie)
    {
        m_nameObject = copie.m_nameObject;
        m_type = copie.m_type;
        m_index = copie.m_index;
        delete m_pos;
        m_pos = new Rectangle(*(copie.m_pos));
        m_value = copie.m_value;
        m_isLooted = copie.m_isLooted;
        m_isDestroyed = copie.m_isDestroyed;
        m_isDropped = copie.m_isDropped;
    }
    return *this;
}

void Object::setDestroyed(bool destroyed)
{
    m_isDestroyed = destroyed;
}

