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
    m_health = health;
    m_maxHealth = health;
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

unsigned int Character::getHealth()
{
    return m_health;
}

unsigned int Character::getMaxHealth()
{
    return m_maxHealth;
}

unsigned int Character::getLevel()
{
    return m_level;
}

unsigned int Character::getDefense()
{
    return m_defense;
}

unsigned int Character::getStrengh()
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

void Character::event(const SDL_Event &event,Character tabCharacter[])
{
    if((m_alive)&&(m_isLoaded))
    {
        if (event.key.keysym.sym == SDLK_z)
        {
            move(Vec2<int>(0,-5));
            m_imCharacter.move(m_position,WINDOW_SIZE);
            crashWithEnemy(tabCharacter,event);
            updateRange(event);
            std::cout<<"touche z appuyée : le joueur monte"<<std::endl;

        }
        if (event.key.keysym.sym == SDLK_s)
        {
            move(Vec2<int>(0,5));
            m_imCharacter.move(m_position,WINDOW_SIZE);
            crashWithEnemy(tabCharacter,event);
            updateRange(event);
            std::cout<<"touche s appuyée : le joueur descend"<<std::endl;
        }
        if (event.key.keysym.sym == SDLK_q)
        {
            move(Vec2<int>(-5,0));
            m_imCharacter.move(m_position,WINDOW_SIZE);
            crashWithEnemy(tabCharacter,event);
            updateRange(event);
            std::cout<<"touche q appuyée : le joueur va a gauche"<<std::endl;
        }
        if (event.key.keysym.sym == SDLK_d)
        {
            move(Vec2<int>(5,0));
            m_imCharacter.move(m_position,WINDOW_SIZE);
            crashWithEnemy(tabCharacter,event);
            updateRange(event);
            std::cout<<"touche d appuyée : le joueur va a droite"<<std::endl;
        }
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            std::cout<<"Le joueur attaque !"<<std::endl;
            for(unsigned int i=0;i<1;i++)
            {
                attack(tabCharacter[i]);
            }
        }
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

bool Character::isAlive()
{
    return m_alive;
}

void Character::knockBack(const SDL_Event &event)
{
    if (event.key.keysym.sym == SDLK_z)
    {
        move(Vec2<int>(0,20));
        m_imCharacter.move(m_position,WINDOW_SIZE);
        std::cout<<"entite repoussee vers le bas"<<std::endl;
    }
    if (event.key.keysym.sym == SDLK_s)
    {
        move(Vec2<int>(0,-20));
        m_imCharacter.move(m_position,WINDOW_SIZE);
        std::cout<<"entite repoussee vers le haut"<<std::endl;
    }
    if (event.key.keysym.sym == SDLK_q)
    {
        move(Vec2<int>(20,0));
        m_imCharacter.move(m_position,WINDOW_SIZE);
        std::cout<<"entite repoussee vers la droite"<<std::endl;
    }
    if (event.key.keysym.sym == SDLK_d)
    {
        move(Vec2<int>(-20,0));
        m_imCharacter.move(m_position,WINDOW_SIZE);
        std::cout<<"entite repoussee vers la gauche"<<std::endl;
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

void Character::updateRange(const SDL_Event &event)
{
    if (event.key.keysym.sym == SDLK_d)
    {
        m_range.rectangle.x = m_position.rectangle.x + m_position.rectangle.w;
        m_range.rectangle.y = m_position.rectangle.y + (m_position.rectangle.h / 4);
        m_range.rectangle.w = m_position.rectangle.w / 2;
        m_range.rectangle.h = m_position.rectangle.h / 2;
    }
    if (event.key.keysym.sym == SDLK_q)
    {
        m_range.rectangle.x = m_position.rectangle.x - m_range.rectangle.w;
        m_range.rectangle.y = m_position.rectangle.y + (m_position.rectangle.h / 4);
        m_range.rectangle.w = m_position.rectangle.w / 2;
        m_range.rectangle.h = m_position.rectangle.h / 2;
    }
    if (event.key.keysym.sym == SDLK_s)
    {
        m_range.rectangle.x = m_position.rectangle.x + (m_position.rectangle.w/4);
        m_range.rectangle.y = m_position.rectangle.y + m_position.rectangle.h;
        m_range.rectangle.w = m_position.rectangle.w / 2;
        m_range.rectangle.h = m_position.rectangle.h / 2;
    }
    if (event.key.keysym.sym == SDLK_z)
    {
        m_range.rectangle.x = m_position.rectangle.x + (m_position.rectangle.w/4);
        m_range.rectangle.y = m_position.rectangle.y - m_range.rectangle.h;
        m_range.rectangle.w = m_position.rectangle.w / 2;
        m_range.rectangle.h = m_position.rectangle.h / 2;
    }
}

void Character::crashWithEnemy(Character tabCharacter[],const SDL_Event &event)
{
    for (unsigned int i=0;i<1;i++)
    {
        if((tabCharacter[i].isAlive())&&(tabCharacter[i].isLoaded()))
        {
            if(getPos().in(tabCharacter[i].getPos()))
            {
                tabCharacter[i].dealDamage(*this);
                std::cout<<"warrior touche ! il perd de la vie ..."<<std::endl;
                std::cout<<"Vie de warrior restante : "<<getHealth()<<" HP"<<std::endl;
                knockBack(event);
            }
        }
    }
}

void Character::setLoaded(bool load)
{
    m_isLoaded = load;
}

bool Character::isLoaded()
{
    return m_isLoaded;
}

