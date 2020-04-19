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
        m_inventory.m_tabEquip[i].m_dropped=false;
        m_inventory.m_tabEquip[i].m_pos=nullptr;

    }
    m_armor.m_defense = 10;
    m_defense += m_armor.m_defense;
    m_tabEquipped[0].m_nameEquipment="beginner weapon";
    m_tabEquipped[0].m_index=0;
    m_tabEquipped[0].m_type=weapon;
    m_tabEquipped[0].m_value=20;
    m_tabEquipped[0].m_isLooted=true;
    m_tabEquipped[0].m_destroyed=false;
    m_tabEquipped[0].m_dropped=false;
    m_tabEquipped[0].m_pos = nullptr;
    m_tabEquipped[1].m_nameEquipment="beginner armor";
    m_tabEquipped[1].m_index=1;
    m_tabEquipped[1].m_type=armor;
    m_tabEquipped[1].m_value=10;
    m_tabEquipped[1].m_isLooted=true;
    m_tabEquipped[1].m_destroyed=false;
    m_tabEquipped[1].m_dropped=false;
    m_tabEquipped[1].m_pos = nullptr;
    m_inventory.m_numEmptySlot = 0;
    m_timer=SDL_GetTicks();
}

Player::Player(const std::string & name,PlayerClass Class, const Rectangle & pos,
               const unsigned int health, const unsigned int level) :
           Character(pos,health,level)
{
    m_xpCurrent = 0;
    m_xpMax = 100;
    for(unsigned int i=0;i<16;i++)
    {
        m_inventory.m_tabEquip[i].m_nameEquipment="no object";
        m_inventory.m_tabEquip[i].m_type=other;
        m_inventory.m_tabEquip[i].m_index=500;
        m_inventory.m_tabEquip[i].m_isLooted=true;
        m_inventory.m_tabEquip[i].m_destroyed=true;
        m_inventory.m_tabEquip[i].m_dropped=false;
        m_inventory.m_tabEquip[i].m_pos=nullptr;

    }
    m_armor.m_defense = 10;
    m_tabEquipped[0].m_nameEquipment="beginner weapon";
    m_tabEquipped[0].m_index=0;
    m_tabEquipped[0].m_type=weapon;
    m_tabEquipped[0].m_value=20;
    m_tabEquipped[0].m_isLooted=true;
    m_tabEquipped[0].m_destroyed=false;
    m_tabEquipped[0].m_dropped=false;
    m_tabEquipped[0].m_pos = nullptr;
    m_tabEquipped[1].m_nameEquipment="beginner armor";
    m_tabEquipped[1].m_index=1;
    m_tabEquipped[1].m_type=armor;
    m_tabEquipped[1].m_value=10;
    m_tabEquipped[1].m_isLooted=true;
    m_tabEquipped[1].m_destroyed=false;
    m_tabEquipped[1].m_dropped=false;
    m_tabEquipped[1].m_pos = nullptr;
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
    m_timer=SDL_GetTicks();
}

unsigned int Player::getXpCurrent() const
{
    return m_xpCurrent;
}

unsigned int Player::getXpMax() const
{
    return m_xpMax;
}

void Player::increaseXp(unsigned int xpGot)
{
    m_xpCurrent += xpGot;
    std::cout<<"Vous avez gagné "<<xpGot<<" xp"<<std::endl;
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
    std::cout<<"Vous avez récupéré tous vos HP !"<<std::endl;
}

void Player::Loot(Object tabObject[],unsigned int sizeTab)
{
    for (unsigned int i=0;i<sizeTab;i++)
    {
        if(getPos().in(*(tabObject[i].m_pos)))
        {
            if((!tabObject[i].m_isLooted)&&(tabObject[i].m_dropped))
            {
                if(m_inventory.m_numEmptySlot<16)
                {
                    tabObject[i].m_isLooted=true;
                    tabObject[i].m_dropped=false;
                    tabObject[i].m_destroyed=false;
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
               std::cout<<"Vous avez déjà tous vos HP !"<<std::endl;
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
    default:
        return "error";
    }
}

void Player::getPlayerStats() const
{
    std::cout<<"### Statistiques du joueur ###"<<std::endl;
    std::cout<<"Nom : "<<getName()<<std::endl;
    std::cout<<"Classe : "<<getNameClass()<<std::endl;
    std::cout<<"Level : "<<getLevel()<<std::endl;
    std::cout<<"Expérience actuelle : "<<getXpCurrent()<<"/"<<getXpMax()<<std::endl;
    std::cout<<"Expérience avant le prochain niveau : "<<getXpMax()-getXpCurrent()<<std::endl;
    std::cout<<"Vie : "<<getHealth()<<"/"<<getMaxHealth()<<" HP"<<std::endl;
    std::cout<<"Force : "<<getStrengh()<<std::endl;
    std::cout<<"Défense : "<<getDefense()<<std::endl<<std::endl;
}

void Player::attack(Enemy & enemy)
{
    if ((m_alive)&&(m_isLoaded)&&(enemy.isAlive())&&(enemy.isLoaded()))
    {
        if (getRange().in(enemy.getPos()))
        {
            if((SDL_GetTicks()-m_timer)>1000)
            {
                std::cout<<"Le joueur attaque !"<<std::endl;
                dealDamage(enemy);
                std::cout<<enemy.getEnemyRace()<<" "<<enemy.getEnemyType()<<
                        " touché ! Il perd de la vie ..."<<std::endl;
                std::cout<<"Vie du "<<enemy.getEnemyRace()<<" "<<enemy.getEnemyType()<<
                           " restante : "<<enemy.getHealth()<<" HP"<<std::endl;
                m_timer=SDL_GetTicks();
            }
        }
    }
}

void Player::dealDamage(Enemy & enemy)
{
    int damageToDeal = m_weapon.m_damage + m_strengh - enemy.getDefense();
    if (damageToDeal > 0)
    {
        enemy.takeDamage(damageToDeal,*this);
    }
}
void Player::kill(Enemy &enemy)
{
    enemy.die(*this);
}

unsigned int Player::getTimer() const
{
    return m_timer;
}
