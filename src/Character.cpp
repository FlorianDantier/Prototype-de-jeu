#include "Character.h"
#include <iostream>

Character::Character()
{
    m_position = Vec2<int>(0,0);
    m_speed = 100;
    m_health = 100;
    m_defense = 5;
    m_strengh = 5;
    m_level = 1;
    m_imCharacter = NULL;
}

Character::Character(const & Vec2<int> pos, unsigned int health, const & Image imChar, unsigned int level)
{
    m_position = pos;
    m_speed = 100;
    m_health = health;
    m_level = level;
    m_defense = level * 5;
    m_strengh = level * 5;
    m_imCharacter = imChar;
}

void Character::move(const & Vec2<int> direction)
{
    m_position += direction ;
}

Rectangle Character::getPos() const
{
    Rectangle(m_position.x,m_position.y,m_imCharacter.m_destination.rectangle.w,m_imCharacter.m_destination.rectangle.h) recPos;
    return recPos;
}

void Character::setPos(const & Rectangle recPos)
{
    m_position = Vec2<int>(recPos.x,recPos.y);
}

void Character::dealDamage(Character & c_ennemi)
{
    int damageToDeal = m_weapon.m_damage + m_strengh - c_ennemi.m_defense;
    if (damageToDeal > 0)
    {
        c_ennemi.m_health -= damageToDeal;
    }
}