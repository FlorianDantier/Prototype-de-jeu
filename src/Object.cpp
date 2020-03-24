#include <iostream>
#include "Object.h"

Object::Object()
{
    m_imObject = NULL;
    m_rarity = common;
    m_name = "unknown object";
    m_looted = false
    m_selected = false;
}

Object::Object(const & Image imObject, Rarity rarity, const & string name)
{
    m_imObject = imObject;
    m_rarity = rarity;
    m_name = name;
    m_looted = false;
    m_selected = false;
}

void Object::setLooted(bool isLooted)
{
    m_looted = isLooted;
}

void Object::setSelected(bool isSelected)
{
    m_selected = isSelected;
}