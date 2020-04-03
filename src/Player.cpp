#include "Player.h"

Player::Player()
{
    m_name = "unknown player";
    m_class = warrior;
    m_xpCurrent = 0;
    m_xpMax = 100;
    for(unsigned int i=0;i<16;i++)
    {
        m_inventory.m_tabEquip[i].m_nameEquipment="no object";
        m_inventory.m_tabEquip[i].m_type=other;
        m_inventory.m_tabEquip[i].m_index=500;
        m_inventory.m_tabEquip[i].m_isLooted=true;
    }
    m_armor.m_defense = 10;
    m_defense += m_armor.m_defense;
    m_tabEquipped[0].m_nameEquipment="beginner weapon";
    m_tabEquipped[1].m_nameEquipment="beginner armor";
    m_inventory.m_numEmptySlot = 0;
}

Player::Player(const std::string & name,PlayerClass Class,const Rectangle & pos,
               const unsigned int health,const unsigned int level,
               const std::string & imPath,SDL_Renderer *renderer) :
           Character(pos,health,imPath,renderer,level)
{
    m_xpCurrent = 0;
    m_xpMax = 100;
    for(unsigned int i=0;i<16;i++)
    {
        m_inventory.m_tabEquip[i].m_nameEquipment="no object";
        m_inventory.m_tabEquip[i].m_type=other;
        m_inventory.m_tabEquip[i].m_index=500;
        m_inventory.m_tabEquip[i].m_isLooted=true;
    }
    m_armor.m_defense = 10;
    m_tabEquipped[0].m_nameEquipment="beginner weapon";
    m_tabEquipped[1].m_nameEquipment="beginner armor";
    m_inventory.m_numEmptySlot = 0;
    m_name = name;
    m_class = Class;
    if (m_class==warrior)
    {
        m_strengh += 10;
        m_health += 20;
    }
    if (m_class==archer)
    {
        m_health -= 10;
    }
    if (m_class==mage)
    {
        m_health -= 10;
    }
}

unsigned int Player::getXpCurrent() const
{
    return m_xpCurrent;
}

unsigned int Player::getXpMax() const
{
    return m_xpMax;
}

void Player::levelup()
{
    m_strengh+=10;
    m_maxHealth +=20;
    m_health=m_maxHealth;
    m_defense+=5;
    m_xpMax+=100*m_level;
    m_xpCurrent=0;
    m_level++;
    std::cout<<"Level up ! Niveau actuel : "<<m_level<<std::endl;
}

void Player::Loot(Equipment tabObject[],unsigned int sizeTab)
{
    for (unsigned int i=0;i<sizeTab;i++)
    {
        if(getPos().in(tabObject[i].m_pos))
        {
            if(!tabObject[i].m_isLooted)
            {
                if(m_inventory.m_numEmptySlot<16)
                {
                    tabObject[i].m_isLooted=true;
                    m_inventory.m_tabEquip[m_inventory.m_numEmptySlot]=tabObject[i];
                    m_inventory.m_tabEquip[m_inventory.m_numEmptySlot].m_index= m_inventory.m_numEmptySlot;
                    m_inventory.m_numEmptySlot++;
                }
                else
                {
                    std::cout<<"Inventaire plein !"<<std::endl;
                }
            }
        }
    }

}

void Player::Equip(Equipment & equipment)
{
    Equipment temp;
    if(equipment.m_type==weapon)
    {
        m_tabEquipped[0].m_index=equipment.m_index;
        temp=m_tabEquipped[0];
        m_tabEquipped[0]=equipment;
        m_inventory.m_tabEquip[temp.m_index]=temp;
    }
    else if(equipment.m_type==armor)
    {
        m_tabEquipped[1].m_index=equipment.m_index;
        temp=m_tabEquipped[1];
        m_tabEquipped[1]=equipment;
        m_inventory.m_tabEquip[temp.m_index]=temp;
    }
}


void Player::openInventory() const
{
    for (unsigned int i=0;i<16;i++)
    {
        if(m_inventory.m_tabEquip[i].m_nameEquipment!="no object")
        {
            std::cout<<"item slot "<<i<<" : "<<
                       m_inventory.m_tabEquip[i].m_nameEquipment<<std::endl<<
                       m_inventory.m_tabEquip[i].m_type<<std::endl;
        }
    }
}
