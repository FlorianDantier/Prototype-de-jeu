#include "Character.h"
#include <iostream>
#include "common.h"

Character::Character()
{
    m_health = 100;
    m_maxHealth = 100;
    m_defense = 5;
    m_strengh = 5;
    m_level = 1;
    m_weapon.m_damage = 20;
    m_alive = false;
    m_isLoaded = false;
    m_isXpGiven = false;
    m_position = nullptr;
    m_range = nullptr;
}

Character::Character(const Rectangle & pos, unsigned int health,
                     unsigned int level)
{
    m_position = new Rectangle(pos);
    m_range = new Rectangle;
    m_range->m_position.x = pos.m_position.x + pos.m_dimension.x;
    m_range->m_position.y = pos.m_position.y + (pos.m_dimension.y / 4);
    m_range->m_dimension.x = pos.m_dimension.x / 2;
    m_range->m_dimension.y = pos.m_dimension.y / 2;
    m_maxHealth = health;
    m_health = health;
    m_level = level;
    m_defense = level * 5;
    m_strengh = level * 5;
    m_weapon.m_damage = 20;
    m_alive = true;
    m_isLoaded = true;
    m_isXpGiven = false;
    m_orient = south;
}

Character::~Character()
{
    delete m_position;
    delete m_range;
    m_position = nullptr;
    m_range = nullptr;
}

void Character::move(const Vec2<int> & direction)
{
    m_position->m_position.x += direction.x;
    m_position->m_position.y += direction.y;
    if(direction == top)
    {
        m_orient = north;
    }
    else if(direction == bottom)
    {
        m_orient = south;
    }
    else if(direction == left)
    {
        m_orient = west;
    }
    else if(direction == right)
    {
        m_orient = east;
    }
}

Rectangle& Character::getPos() const
{
    return *m_position;
}

void Character::setPos(const Rectangle & recPos)
{
    *m_position = recPos;
}
void Character::takeDamage(unsigned int damageToDeal,Character & enemy)
{
    if (damageToDeal>=m_health)
    {
        m_health = 0;
        enemy.kill(*this);
    }
    else
    {
        m_health -= damageToDeal;
    }
}
void Character::dealDamage(Character & c_enemy)
{
    int damageToDeal = m_weapon.m_damage + m_strengh - c_enemy.m_defense;
    if (damageToDeal > 0)
    {
        c_enemy.takeDamage(damageToDeal,*this);
    }
}

unsigned int Character::getHealth() const
{
    return m_health;
}

unsigned int Character::getMaxHealth() const
{
    return m_maxHealth;
}

unsigned int Character::getLevel() const
{
    return m_level;
}

unsigned int Character::getDefense() const
{
    return m_defense;
}

unsigned int Character::getStrengh() const
{
    return m_strengh;
}

Rectangle& Character::getRange() const
{
    return *m_range;
}

void Character::setHealth(const unsigned int health)
{
    m_health = health;
}

void Character::setMaxHealth(const unsigned int maxHealth)
{
    m_maxHealth = maxHealth;
}

void Character::setLevel(const unsigned int level)
{
    m_level = level;
}

void Character::setDefense(const unsigned int defense)
{
    m_defense = defense;
}

void Character::setStrengh(const unsigned int strengh)
{
    m_strengh = strengh;
}

void Character::setRange(Rectangle * range)
{
    m_range = range;
}

void Character::updatePlayerMoveRight(Character tabCharacter[],
                                      unsigned int sizeTab)
{
        crashWithEnemyOnRight(tabCharacter,sizeTab);
        updateRangeRight();
        //std::cout<<"touche d appuyée : le joueur va a droite"<<std::endl;
}

void Character::updatePlayerMoveLeft(Character tabCharacter[],
                                     unsigned int sizeTab)
{
        crashWithEnemyOnLeft(tabCharacter,sizeTab);
        updateRangeLeft();
        //std::cout<<"touche q appuyée : le joueur va a gauche"<<std::endl;
}

void Character::updatePlayerMoveTop(Character tabCharacter[],
                                    unsigned int sizeTab)
{
        crashWithEnemyOnTop(tabCharacter,sizeTab);
        updateRangeTop();
        //std::cout<<"touche z appuyée : le joueur monte"<<std::endl;
}

void Character::updatePlayerMoveBottom(Character tabCharacter[],
                                       unsigned int sizeTab)
{
        crashWithEnemyOnBottom(tabCharacter,sizeTab);
        updateRangeBottom();
        //std::cout<<"touche s appuyée : le joueur descend"<<std::endl;
}

void Character::display()
{
    if((m_alive)&&(m_isLoaded))
    {
        //m_imCharacter.display();
    }
}

Vec2<int> Character::getVecPos()
{
    return {m_position->m_position.x,m_position->m_position.y};
}

void Character::die()
{
    std::cout<<"mort d'une entite"<<std::endl;
    m_alive = false;
    m_isLoaded = false;
}

bool Character::isAlive() const
{
    return m_alive;
}

void Character::knockBackRight()
{
    move(Vec2<int>(20,0));
    if(testInOut())
    {
        std::cout<<"entite repoussee vers la droite"<<std::endl;
    }
}

void Character::knockBackLeft()
{
    move(Vec2<int>(-20,0));
    if(testInOut())
    {
        std::cout<<"entite repoussee vers la gauche"<<std::endl;
    }
}

void Character::knockBackTop()
{
    move(Vec2<int>(0,-20));
    if(testInOut())
    {
        std::cout<<"entite repoussee vers le haut"<<std::endl;
    }
}

void Character::knockBackBottom()
{
    move(Vec2<int>(0,20));
    if(testInOut())
    {
        std::cout<<"entite repoussee vers le bas"<<std::endl;
    }
}

void Character::kill(Character &enemy)
{
    enemy.die();
}

void Character::attack(Character & enemy)
{
    if ((m_alive)&&(m_isLoaded)&&(enemy.isAlive())&&(enemy.isLoaded()))
    {
        if (getRange().in(enemy.getPos()))
        {
            dealDamage(enemy);
            std::cout<<"Un ennemi attaque !"<<std::endl;
            std::cout<<"joueur touche ! il perd de la vie ..."<<std::endl;
            std::cout<<"Vie du joueur restante : "<<enemy.getHealth()
                    <<" HP"<<std::endl;
        }
    }
}

void Character::updateRangeRight()
{
    m_range->m_position.x = m_position->m_position.x +
            m_position->m_dimension.x;
    m_range->m_position.y = m_position->m_position.y +
            (m_position->m_dimension.y / 4);
    m_range->m_dimension.x = m_position->m_dimension.x / 2;
    m_range->m_dimension.y = m_position->m_dimension.y / 2;
}

void Character::updateRangeLeft()
{
    m_range->m_position.x = m_position->m_position.x -
            m_range->m_dimension.x;
    m_range->m_position.y = m_position->m_position.y +
            (m_position->m_dimension.y / 4);
    m_range->m_dimension.x = m_position->m_dimension.x / 2;
    m_range->m_dimension.y = m_position->m_dimension.y / 2;
}

void Character::updateRangeTop()
{
    m_range->m_position.x = m_position->m_position.x +
            (m_position->m_dimension.x/4);
    m_range->m_position.y = m_position->m_position.y -
            m_range->m_dimension.y;
    m_range->m_dimension.x = m_position->m_dimension.x / 2;
    m_range->m_dimension.y = m_position->m_dimension.y / 2;
}

void Character::updateRangeBottom()
{
    m_range->m_position.x = m_position->m_position.x +
            (m_position->m_dimension.x/4);
    m_range->m_position.y = m_position->m_position.y +
            m_position->m_dimension.y;
    m_range->m_dimension.x = m_position->m_dimension.x / 2;
    m_range->m_dimension.y = m_position->m_dimension.y / 2;
}

void Character::crashWithEnemyOnRight(Character tabCharacter[],
                                      unsigned int sizeTab)
{
    for (unsigned int i=0;i<sizeTab;i++)
    {
        if((tabCharacter[i].isAlive())&&(tabCharacter[i].isLoaded()))
        {
            if(getPos().in(tabCharacter[i].getPos()))
            {
                tabCharacter[i].dealDamage(*this);
                std::cout<<"warrior touche ! il perd de la vie ..."<<std::endl;
                std::cout<<"Vie de warrior restante : "<<getHealth()
                        <<" HP"<<std::endl;
                knockBackLeft();
            }
        }
    }
}

void Character::crashWithEnemyOnLeft(Character tabCharacter[],
                                     unsigned int sizeTab)
{
    for (unsigned int i=0;i<sizeTab;i++)
    {
        if((tabCharacter[i].isAlive())&&(tabCharacter[i].isLoaded()))
        {
            if(getPos().in(tabCharacter[i].getPos()))
            {
                tabCharacter[i].dealDamage(*this);
                std::cout<<"warrior touche ! il perd de la vie ..."<<std::endl;
                std::cout<<"Vie de warrior restante : "<<getHealth()
                        <<" HP"<<std::endl;
                knockBackRight();
            }
        }
    }
}

void Character::crashWithEnemyOnBottom(Character tabCharacter[],
                                       unsigned int sizeTab)
{
    for (unsigned int i=0;i<sizeTab;i++)
    {
        if((tabCharacter[i].isAlive())&&(tabCharacter[i].isLoaded()))
        {
            if(getPos().in(tabCharacter[i].getPos()))
            {
                tabCharacter[i].dealDamage(*this);
                std::cout<<"warrior touche ! il perd de la vie ..."<<std::endl;
                std::cout<<"Vie de warrior restante : "<<getHealth()
                        <<" HP"<<std::endl;
                knockBackTop();
            }
        }
    }
}

void Character::crashWithEnemyOnTop(Character tabCharacter[],
                                    unsigned int sizeTab)
{
    for (unsigned int i=0;i<sizeTab;i++)
    {
        if((tabCharacter[i].isAlive())&&(tabCharacter[i].isLoaded()))
        {
            if(getPos().in(tabCharacter[i].getPos()))
            {
                tabCharacter[i].dealDamage(*this);
                std::cout<<"warrior touche ! il perd de la vie ..."<<std::endl;
                std::cout<<"Vie de warrior restante : "<<getHealth()
                        <<" HP"<<std::endl;
                knockBackBottom();
            }
        }
    }
}

void Character::setLoaded(bool load)
{
    m_isLoaded = load;
}

bool Character::isLoaded() const
{
    return m_isLoaded;
}

bool Character::testInOut()
{
    if(m_position->m_position.x<0)
    {
        m_position->m_position.x=0;
        return false;
    }
    if(m_position->m_position.y<0)
    {
        m_position->m_position.y=0;
        return false;
    }
    if((m_position->m_position.x + m_position->m_dimension.x) > windowSize.x)
    {
        m_position->m_position.x = windowSize.x - m_position->m_dimension.x;
        return false;
    }
    if((m_position->m_position.y + m_position->m_dimension.y) > windowSize.y)
    {
        m_position->m_position.y = windowSize.y - m_position->m_dimension.y;
        return false;
    }
    return true;
}

void Character::setOrientation(const Orientation orient)
{
    m_orient = orient;
}

Orientation Character::getOrientation() const
{
    return m_orient;
}

Character &Character::operator=(const Character &copie)
{
    if (this != &copie)
    {
        delete m_position;
        m_position = new Rectangle(*(copie.m_range));
        delete m_range;
        m_range = new Rectangle(*(copie.m_position));
        m_maxHealth = copie.m_health;
        m_health = copie.m_health;
        m_level = copie.m_level;
        m_defense = copie.m_level * 5;
        m_strengh = copie.m_level * 5;
        m_weapon.m_damage = 20;
        m_alive = copie.m_alive;
        m_isLoaded = copie.m_isLoaded;
        m_isXpGiven = copie.m_isXpGiven;
        m_orient = copie.m_orient;
    }
    return *this;
}

