#include "Player.h"

Player::Player()
{
    m_name = "unknown player";
    m_intelligence = 5;
    m_agility = 5;
    m_mana = 100;
    m_class = warrior;
}

Player::Player(const & string name, Player Class)
{
    m_name = name;
    m_intelligence = 5;
    m_agility = 5;
    m_mana = 100;
    m_class = Class;
    if (m_class==warrior)
    {
        m_strengh += 10;
        m_health = 120;
    }
    if (m_class==archer)
    {
        m_agility += 10;
        m_health = 90;
    }
    if (m_class==mage)
    {
        m_intelligence += 10;
        m_health = 90;
    }
}

void Player::Loot(Object & object)
{
    object.setLooted(true);
    m_inventory.addObject(object);
}

void Player::Equip(Equipment & equipment)
{
    equipment.setEquipped(true);
    if (equipment.type == weapon)
    {
        m_weapon.setEquipped(false);
        m_inventory.addObject(m_weapon);
        m_weapon = equipment;
    }
    if (equipment.type == armor)
    {
        m_armor.setEquipped(false);
        m_inventory.addObject(m_armor);
        m_armor = equipment;
    }
    m_inventory.removeObject(equipment);
}