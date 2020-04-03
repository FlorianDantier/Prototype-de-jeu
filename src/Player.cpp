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
        m_inventory.m_tabEquip[i].m_destroyed=true;
    }
    m_armor.m_defense = 10;
    m_defense += m_armor.m_defense;
    m_tabEquipped[0].m_nameEquipment="beginner weapon";
    m_tabEquipped[0].m_index=0;
    m_tabEquipped[0].m_type=weapon;
    m_tabEquipped[0].m_value=20;
    m_tabEquipped[0].m_isLooted=true;
    m_tabEquipped[0].m_destroyed=false;
    m_tabEquipped[1].m_nameEquipment="beginner armor";
    m_tabEquipped[1].m_index=1;
    m_tabEquipped[1].m_type=armor;
    m_tabEquipped[1].m_value=10;
    m_tabEquipped[1].m_isLooted=true;
    m_tabEquipped[1].m_destroyed=false;
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
    m_tabEquipped[0].m_index=0;
    m_tabEquipped[0].m_type=weapon;
    m_tabEquipped[0].m_value=20;
    m_tabEquipped[0].m_isLooted=true;
    m_tabEquipped[0].m_destroyed=false;
    m_tabEquipped[1].m_nameEquipment="beginner armor";
    m_tabEquipped[1].m_index=1;
    m_tabEquipped[1].m_type=armor;
    m_tabEquipped[1].m_value=10;
    m_tabEquipped[1].m_isLooted=true;
    m_tabEquipped[1].m_destroyed=false;
    m_inventory.m_numEmptySlot = 0;
    m_name = name;
    m_class = Class;
    if (m_class==warrior)
    {
        m_strengh += 10;
        m_health += 20;
        m_maxHealth += 20;
    }
    if (m_class==archer)
    {
        m_health -= 10;
        m_maxHealth -= 10;
    }
    if (m_class==mage)
    {
        m_health -= 10;
        m_maxHealth -= 10;
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

void Player::Loot(Object tabObject[],unsigned int sizeTab)
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
                    std::cout<<"Objet "<<tabObject[i].m_nameEquipment<<" obtenu !"<<std::endl;
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

void Player::Equip(Object & equipment)
{
    if(!equipment.m_destroyed)
    {
        if(equipment.m_nameEquipment!="no object")
        {
            Object temp;
            if(equipment.m_type==weapon)
            {
                m_tabEquipped[0].m_index=equipment.m_index;
                temp=m_tabEquipped[0];
                m_tabEquipped[0]=equipment;
                m_weapon.m_damage = equipment.m_value;
                std::cout<<"Objet "<<equipment.m_nameEquipment<<" équipé !"<<std::endl;
                m_inventory.m_tabEquip[temp.m_index]=temp;
            }
            else if(equipment.m_type==armor)
            {
                m_tabEquipped[1].m_index=equipment.m_index;
                temp=m_tabEquipped[1];
                m_tabEquipped[1]=equipment;
                m_defense -= m_armor.m_defense;
                m_armor.m_defense = equipment.m_value;
                m_defense += m_armor.m_defense;
                std::cout<<"Objet "<<equipment.m_nameEquipment<<" équipé !"<<std::endl;
                m_inventory.m_tabEquip[temp.m_index]=temp;
            }
            else
            {
                std::cout<<"Objet non équipable !"<<std::endl;
            }
        }
    }
}

void Player::Use(Object &consumable)
{
    if(consumable.m_nameEquipment!="no object")
    {
        if((consumable.m_type==other)&&(!consumable.m_destroyed))
        {
            if(m_health!=m_maxHealth)
            {
                unsigned int healAmount = consumable.m_value;
                if(m_health + healAmount > m_maxHealth)
                {
                    m_health = m_maxHealth;
                }
                else
                {
                    m_health += healAmount;
                }
                std::cout<<"Objet "<<consumable.m_nameEquipment<<" utilisé !"<<std::endl;
                std::cout<<"Vous avez "<<m_health<<" hp"<<std::endl;
                consumable.m_destroyed = true;
                deleteObject(consumable.m_index);
                std::cout<<"Objet "<<consumable.m_nameEquipment<<" détruit !"<<std::endl;
            }
            else
            {
               std::cout<<"Vous avez déjà tous vos points de vies !"<<std::endl;
            }
        }
        else
        {
            std::cout<<"Objet non utilisable !"<<std::endl;
        }
    }
}

void Player::deleteObject(unsigned int index)
{
    for (unsigned int i=index;i<15;i++)
    {
            m_inventory.m_tabEquip[i]=m_inventory.m_tabEquip[i+1];
            m_inventory.m_tabEquip[i].m_index--;
    }
     m_inventory.m_tabEquip[15].m_nameEquipment="no object";
     m_inventory.m_tabEquip[15].m_destroyed=true;
     m_inventory.m_numEmptySlot--;
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

std::string Player::getName() const
{
    return m_name;
}

std::string Player::getNameClass() const
{
    switch(m_class)
    {

    case 0:
        return "Warrior";
    case 1:
        return "Archer";
    case 2:
        return "Mage";
    }
}

