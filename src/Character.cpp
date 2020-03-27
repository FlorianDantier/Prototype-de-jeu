#include "Character.h"
#include <iostream>

Character::Character()
{
    m_speed = 100;
    m_health = 100;
    m_defense = 5;
    m_strengh = 5;
    m_level = 1;
    m_weapon.m_damage = 20;
    m_alive = true;
}

Character::Character(const Rectangle & pos, unsigned int health, const std::string & imPath, SDL_Renderer *renderer, unsigned int level)
    : m_imCharacter(imPath,pos,Vec2<unsigned int>(640,480),renderer)
{
    m_position = pos;
    m_speed = 100;
    m_health = health;
    m_level = level;
    m_defense = level * 5;
    m_strengh = level * 5;
    m_weapon.m_damage = 20;
    m_alive = true;
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
void Character::takeDamage(unsigned int damageToDeal)
{
    if (damageToDeal>m_health)
    {
        m_health = 0;
        m_alive = false;
        die();
    }
    else
    {
        m_health -= damageToDeal;
    }
}
void Character::dealDamage(Character & c_ennemi)
{
    int damageToDeal = m_weapon.m_damage + m_strengh - c_ennemi.m_defense;
    if (damageToDeal > 0)
    {
        c_ennemi.takeDamage(damageToDeal);
    }
}

unsigned int Character::getHealth()
{
    return m_health;
}

void Character::event(const SDL_Event &event)
{
    if (event.key.keysym.sym == SDLK_z)
    {
        for (unsigned int i=0;i<5;i++)
        {
            move(Vec2<int>(0,-1));
            m_imCharacter.moveTop(Vec2<unsigned int>(640,480));
        }
        std::cout<<"monte"<<std::endl;
    }
    if (event.key.keysym.sym == SDLK_s)
    {
        for (unsigned int i=0;i<5;i++)
        {
            move(Vec2<int>(0,1));
            m_imCharacter.moveBottom(Vec2<unsigned int>(640,480));
        }
        std::cout<<"descend"<<std::endl;
    }
    if (event.key.keysym.sym == SDLK_q)
    {
        for (unsigned int i=0;i<5;i++)
        {
            move(Vec2<int>(-1,0));
            m_imCharacter.moveLeft(Vec2<unsigned int>(640,480));
        }
        std::cout<<"gauche"<<std::endl;
    }
    if (event.key.keysym.sym == SDLK_d)
    {
        for (unsigned int i=0;i<5;i++)
        {
            move(Vec2<int>(1,0));
            m_imCharacter.moveRight(Vec2<unsigned int>(640,480));
        }
        std::cout<<"droite"<<std::endl;
    }
}

void Character::display(SDL_Renderer *renderer)
{
    m_imCharacter.display(renderer);
}

Vec2<int> Character::getVecPos()
{
    return Vec2(m_position.rectangle.x,m_position.rectangle.y);
}

void Character::die()
{
    std::cout<<"mort d'une entite"<<std::endl;
}

bool Character::isAlive()
{
    return m_alive;
}

void Character::knockBack(const SDL_Event &event)
{
    if (event.key.keysym.sym == SDLK_z)
    {
        for (unsigned int i=0;i<20;i++)
        {
            move(Vec2<int>(0,1));
            m_imCharacter.moveBottom(Vec2<unsigned int>(640,480));
        }
        std::cout<<"entite repoussee vers le bas"<<std::endl;
    }
    if (event.key.keysym.sym == SDLK_s)
    {
        for (unsigned int i=0;i<20;i++)
        {
            move(Vec2<int>(0,-1));
            m_imCharacter.moveTop(Vec2<unsigned int>(640,480));
        }
        std::cout<<"entite repoussee vers le haut"<<std::endl;
    }
    if (event.key.keysym.sym == SDLK_q)
    {
        for (unsigned int i=0;i<20;i++)
        {
            move(Vec2<int>(1,0));
            m_imCharacter.moveRight(Vec2<unsigned int>(640,480));
        }
        std::cout<<"entite repoussee vers la droite"<<std::endl;
    }
    if (event.key.keysym.sym == SDLK_d)
    {
        for (unsigned int i=0;i<20;i++)
        {
            move(Vec2<int>(-1,0));
            m_imCharacter.moveLeft(Vec2<unsigned int>(640,480));
        }
        std::cout<<"entite repoussee vers la gauche"<<std::endl;
    }
}
