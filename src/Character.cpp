#include "Character.h"
#include <iostream>

const Vec2<unsigned int> WINDOW_SIZE(640,480);

Character::Character()
{
    m_health = 100;
    m_maxHealth = 100;
    m_defense = 5;
    m_strengh = 5;
    m_level = 1;
    m_weapon.m_damage = 20;
    m_alive = true;
    m_isLoaded = true;
}

Character::Character(const Rectangle & pos, unsigned int health,
                     const std::string & imPath, SDL_Renderer *renderer,
                     unsigned int level)
    : m_imCharacter(imPath,pos,WINDOW_SIZE,renderer)
{
    m_position = pos;
    m_range.rectangle.x = pos.rectangle.x + pos.rectangle.w;
    m_range.rectangle.y = pos.rectangle.y + (pos.rectangle.h / 4);
    m_range.rectangle.w = pos.rectangle.w / 2;
    m_range.rectangle.h = pos.rectangle.h / 2;
    m_maxHealth = health;
    m_health = health;
    m_level = level;
    m_defense = level * 5;
    m_strengh = level * 5;
    m_weapon.m_damage = 20;
    m_alive = true;
    m_isLoaded = true;
}

void Character::move(const Vec2<int> & direction)
{
    m_position.rectangle.x += direction.x;
    m_position.rectangle.y += direction.y;
}

Rectangle Character::getPos() const
{
    return m_position;
}

void Character::setPos(const Rectangle & recPos)
{
    m_position = recPos;
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

Rectangle Character::getRange() const
{
    return m_range;
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

void Character::setRange(const Rectangle &range)
{
    m_range = range;
}

void Character::updatePlayerMoveRight(Character tabCharacter[],unsigned int sizeTab)
{
    move(Vec2<int>(5,0));
    if(testInOut())
    {
        m_imCharacter.move(m_position,WINDOW_SIZE);
        crashWithEnemyOnRight(tabCharacter,sizeTab);
        updateRangeRight();
        std::cout<<"touche d appuyée : le joueur va a droite"<<std::endl;
    }
}

void Character::updatePlayerMoveLeft(Character tabCharacter[],unsigned int sizeTab)
{
    move(Vec2<int>(-5,0));
    if(testInOut())
    {
        m_imCharacter.move(m_position,WINDOW_SIZE);
        crashWithEnemyOnLeft(tabCharacter,sizeTab);
        updateRangeLeft();
        std::cout<<"touche q appuyée : le joueur va a gauche"<<std::endl;
    }
}

void Character::updatePlayerMoveTop(Character tabCharacter[],unsigned int sizeTab)
{
    move(Vec2<int>(0,-5));
    if(testInOut())
    {
        m_imCharacter.move(m_position,WINDOW_SIZE);
        crashWithEnemyOnTop(tabCharacter,sizeTab);
        updateRangeTop();
        std::cout<<"touche z appuyée : le joueur monte"<<std::endl;
    }
}

void Character::updatePlayerMoveBottom(Character tabCharacter[],unsigned int sizeTab)
{
    move(Vec2<int>(0,5));
    if(testInOut())
    {
        m_imCharacter.move(m_position,WINDOW_SIZE);
        crashWithEnemyOnBottom(tabCharacter,sizeTab);
        updateRangeBottom();
        std::cout<<"touche s appuyée : le joueur descend"<<std::endl;
    }
}

void Character::display(SDL_Renderer *renderer)
{
    if((m_alive)&&(m_isLoaded))
    {
        m_imCharacter.display(renderer);
    }
}

Vec2<int> Character::getVecPos()
{
    return {m_position.rectangle.x,m_position.rectangle.y};
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
        m_imCharacter.move(m_position,WINDOW_SIZE);
        std::cout<<"entite repoussee vers la droite"<<std::endl;
    }
}

void Character::knockBackLeft()
{
    move(Vec2<int>(-20,0));
    if(testInOut())
    {
        m_imCharacter.move(m_position,WINDOW_SIZE);
        std::cout<<"entite repoussee vers la gauche"<<std::endl;
    }
}

void Character::knockBackTop()
{
    move(Vec2<int>(0,-20));
    if(testInOut())
    {
        m_imCharacter.move(m_position,WINDOW_SIZE);
        std::cout<<"entite repoussee vers le haut"<<std::endl;
    }
}

void Character::knockBackBottom()
{
    move(Vec2<int>(0,20));
    if(testInOut())
    {
        m_imCharacter.move(m_position,WINDOW_SIZE);
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
            std::cout<<"entite touche ! elle perd de la vie ..."<<std::endl;
            std::cout<<"Vie de l'entite restante : "<<enemy.getHealth()<<" HP"<<std::endl;
        }
    }
}

void Character::updateRangeRight()
{
    m_range.rectangle.x = m_position.rectangle.x + m_position.rectangle.w;
    m_range.rectangle.y = m_position.rectangle.y + (m_position.rectangle.h / 4);
    m_range.rectangle.w = m_position.rectangle.w / 2;
    m_range.rectangle.h = m_position.rectangle.h / 2;
}

void Character::updateRangeLeft()
{
    m_range.rectangle.x = m_position.rectangle.x - m_range.rectangle.w;
    m_range.rectangle.y = m_position.rectangle.y + (m_position.rectangle.h / 4);
    m_range.rectangle.w = m_position.rectangle.w / 2;
    m_range.rectangle.h = m_position.rectangle.h / 2;
}

void Character::updateRangeTop()
{
    m_range.rectangle.x = m_position.rectangle.x + (m_position.rectangle.w/4);
    m_range.rectangle.y = m_position.rectangle.y - m_range.rectangle.h;
    m_range.rectangle.w = m_position.rectangle.w / 2;
    m_range.rectangle.h = m_position.rectangle.h / 2;
}

void Character::updateRangeBottom()
{
    m_range.rectangle.x = m_position.rectangle.x + (m_position.rectangle.w/4);
    m_range.rectangle.y = m_position.rectangle.y + m_position.rectangle.h;
    m_range.rectangle.w = m_position.rectangle.w / 2;
    m_range.rectangle.h = m_position.rectangle.h / 2;
}

void Character::crashWithEnemyOnRight(Character tabCharacter[],unsigned int sizeTab)
{
    for (unsigned int i=0;i<sizeTab;i++)
    {
        if((tabCharacter[i].isAlive())&&(tabCharacter[i].isLoaded()))
        {
            if(getPos().in(tabCharacter[i].getPos()))
            {
                tabCharacter[i].dealDamage(*this);
                std::cout<<"warrior touche ! il perd de la vie ..."<<std::endl;
                std::cout<<"Vie de warrior restante : "<<getHealth()<<" HP"<<std::endl;
                knockBackLeft();
            }
        }
    }
}

void Character::crashWithEnemyOnLeft(Character tabCharacter[],unsigned int sizeTab)
{
    for (unsigned int i=0;i<sizeTab;i++)
    {
        if((tabCharacter[i].isAlive())&&(tabCharacter[i].isLoaded()))
        {
            if(getPos().in(tabCharacter[i].getPos()))
            {
                tabCharacter[i].dealDamage(*this);
                std::cout<<"warrior touche ! il perd de la vie ..."<<std::endl;
                std::cout<<"Vie de warrior restante : "<<getHealth()<<" HP"<<std::endl;
                knockBackRight();
            }
        }
    }
}

void Character::crashWithEnemyOnBottom(Character tabCharacter[],unsigned int sizeTab)
{
    for (unsigned int i=0;i<sizeTab;i++)
    {
        if((tabCharacter[i].isAlive())&&(tabCharacter[i].isLoaded()))
        {
            if(getPos().in(tabCharacter[i].getPos()))
            {
                tabCharacter[i].dealDamage(*this);
                std::cout<<"warrior touche ! il perd de la vie ..."<<std::endl;
                std::cout<<"Vie de warrior restante : "<<getHealth()<<" HP"<<std::endl;
                knockBackTop();
            }
        }
    }
}

void Character::crashWithEnemyOnTop(Character tabCharacter[],unsigned int sizeTab)
{
    for (unsigned int i=0;i<sizeTab;i++)
    {
        if((tabCharacter[i].isAlive())&&(tabCharacter[i].isLoaded()))
        {
            if(getPos().in(tabCharacter[i].getPos()))
            {
                tabCharacter[i].dealDamage(*this);
                std::cout<<"warrior touche ! il perd de la vie ..."<<std::endl;
                std::cout<<"Vie de warrior restante : "<<getHealth()<<" HP"<<std::endl;
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
    if(m_position.rectangle.x<0)
    {
        m_position.rectangle.x=0;
        return false;
    }
    if(m_position.rectangle.y<0)
    {
        m_position.rectangle.y=0;
        return false;
    }
    if((m_position.rectangle.x + m_position.rectangle.w) > WINDOW_SIZE.x)
    {
        m_position.rectangle.x = WINDOW_SIZE.x - m_position.rectangle.w;
        return false;
    }
    if((m_position.rectangle.y + m_position.rectangle.h) > WINDOW_SIZE.y)
    {
        m_position.rectangle.y = WINDOW_SIZE.y - m_position.rectangle.h;
        return false;
    }
    return true;
}

