#include "Player.h"


Player::Player()
{
    m_name = "unknown player";
    m_class = warrior;
    m_xpCurrent = 0;
    m_xpMax = 100;
    for(unsigned int i=0;i<16;i++)
    {
        m_inventory.m_tabEquip[i] = Object();
    }
    m_armor.m_defense = 10;
    m_defense += m_armor.m_defense;
    m_tabEquipped[0] = Object("beginner weapon",weapon,0,
                              getPos(),20,true,false);
    m_tabEquipped[1] = Object("beginner armor",armor,1,
                              getPos(),10,true,false);
    m_inventory.m_numEmptySlot = 0;
    m_timer=time(NULL);
}

Player::Player(const std::string & name,PlayerClass Class,
               const Rectangle & pos, const unsigned int health,
               const unsigned int level) :
           Character(pos,health,level)
{
    m_xpCurrent = 0;
    m_xpMax = 100;
    for(unsigned int i=0;i<16;i++)
    {
        m_inventory.m_tabEquip[i] = Object("no object",other,500,
                                           getPos(),0,true,false);
    }
    m_armor.m_defense = 10;
    m_tabEquipped[0] = Object("beginner weapon",weapon,0,getPos(),
                              20,true,false);
    m_tabEquipped[1] = Object("beginner armor",armor,1,getPos(),
                              10,true,false);
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
    m_timer=time(NULL);
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
        if(getPos().in(tabObject[i].getPos()))
        {
            if((!tabObject[i].isLooted())&&(tabObject[i].isDropped()))
            {
                if(m_inventory.m_numEmptySlot<16)
                {
                    tabObject[i].setLooted(true);
                    tabObject[i].setDropped(false);
                    tabObject[i].setDestroyed(false);
                    m_inventory.m_tabEquip[m_inventory.m_numEmptySlot]
                            =tabObject[i];
                    std::cout<<"Objet "<<tabObject[i].getNameObject()
                            <<" obtenu !"<<std::endl;
                    m_inventory.m_tabEquip[m_inventory.m_numEmptySlot]
                            .setIndex(m_inventory.m_numEmptySlot);
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
    if(!equipment.isDestroyed())
    {
        if(equipment.getNameObject() != "no object")
        {
            Object temp;
            if(equipment.getType()==weapon)
            {
                m_tabEquipped[0].setIndex(equipment.getIndex());
                temp=m_tabEquipped[0];
                m_tabEquipped[0]=equipment;
                m_weapon.m_damage = equipment.getValue();
                std::cout<<"Objet "<<equipment.getNameObject()
                        <<" équipé !"<<std::endl;
                m_inventory.m_tabEquip[temp.getIndex()]=temp;
            }
            else if(equipment.getType()==armor)
            {
                m_tabEquipped[1].setIndex(equipment.getIndex());
                temp=m_tabEquipped[1];
                m_tabEquipped[1]=equipment;
                m_defense -= m_armor.m_defense;
                m_armor.m_defense = equipment.getValue();
                m_defense += m_armor.m_defense;
                std::cout<<"Objet "<<equipment.getNameObject()
                        <<" équipé !"<<std::endl;
                m_inventory.m_tabEquip[temp.getIndex()]=temp;
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
    if(consumable.getNameObject()!="no object")
    {
        if((consumable.getType()==other)&&(!consumable.isDestroyed()))
        {
            if(m_health!=m_maxHealth)
            {
                unsigned int healAmount = consumable.getValue();
                if(m_health + healAmount > m_maxHealth)
                {
                    m_health = m_maxHealth;
                }
                else
                {
                    m_health += healAmount;
                }
                std::cout<<"Objet "<<consumable.getNameObject()
                        <<" utilisé !"<<std::endl;
                std::cout<<"Vous avez "<<m_health<<" hp"<<std::endl;
                consumable.setDestroyed(true);
                deleteObject(consumable.getIndex());
                std::cout<<"Objet "<<consumable.getNameObject()
                        <<" détruit !"<<std::endl;
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
            m_inventory.m_tabEquip[i].setIndex(m_inventory.m_tabEquip[i]
                                               .getIndex()-1);
    }
     m_inventory.m_tabEquip[15].setNameObject("no object");
     m_inventory.m_tabEquip[15].setDestroyed(true);
     m_inventory.m_numEmptySlot--;
}


void Player::openInventory() const
{
    for (unsigned int i=0;i<16;i++)
    {
        if(m_inventory.m_tabEquip[i].getNameObject()!="no object")
        {
            std::cout<<"item slot "<<i<<" : "<<
                       m_inventory.m_tabEquip[i].getNameObject()<<std::endl<<
                       m_inventory.m_tabEquip[i].getObjectType()<<std::endl;
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
    std::cout<<"Expérience actuelle : "<<getXpCurrent()
            <<"/"<<getXpMax()<<std::endl;
    std::cout<<"Expérience avant le prochain niveau : "
            <<getXpMax()-getXpCurrent()<<std::endl;
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
            if(((time(NULL)-m_timer)+0.7)>1)
            {
            std::cout<<getNameClass()<<" "<<getName()<<" attaque !"<<std::endl;
            dealDamage(enemy);
            std::cout<<enemy.getEnemyRace()<<" "<<enemy.getEnemyType()<<
                    " touché ! Il perd de la vie ..."<<std::endl;
            std::cout<<"Vie du "<<enemy.getEnemyRace()<<" "
                    <<enemy.getEnemyType()<<" restante : "
                   <<enemy.getHealth()<<" HP"<<std::endl;
            m_timer=time(NULL);
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

time_t Player::getTimer() const
{
    return m_timer;
}

Player &Player::operator=(const Player &copie)
{
    if(this != &copie)
    {
        m_xpCurrent = copie.m_xpCurrent;
        m_xpMax = copie.m_xpMax;
        for(unsigned int i=0;i<16;i++)
        {
            m_inventory.m_tabEquip[i] = copie.m_inventory.m_tabEquip[i];
        }
        m_armor.m_defense = copie.m_armor.m_defense;
        m_tabEquipped[0] = copie.m_tabEquipped[0];
        m_tabEquipped[1] = copie.m_tabEquipped[1];
        m_inventory.m_numEmptySlot = copie.m_inventory.m_numEmptySlot;
        m_name = copie.m_name;
        m_class = copie.m_class;
        m_strengh = copie.m_strengh;
        m_health = copie.m_health;
        m_maxHealth = copie.m_maxHealth;
        m_timer=copie.m_timer;
    }
    return *this;
}

void Player::setHealth(const unsigned int health)
{
    if((health>m_maxHealth)&&(m_health<m_maxHealth))
    {
        m_health = m_maxHealth;
    }
    else if ((health>m_maxHealth)&&(m_health==m_maxHealth))
    {
        std::cout<<"Vous avez déjà tout vos HP !"<<std::endl;
    }
    else
    {
        m_health = health;
    }
}
