#include "Enemy.h"
#include <time.h>
#include <math.h>

const Vec2<unsigned int> WINDOW_SIZE(640,480);

// On suppose a<b
int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

Enemy::Enemy()
{
    m_hasLoot = false;
    m_loot.m_nameEquipment="no object";
    m_loot.m_type=other;
    m_loot.m_index=500;
    m_loot.m_isLooted=false;
    m_loot.m_destroyed=true;
    m_loot.m_dropped=false;
    m_hasChest = false;
    for(unsigned int i = 0;i<3;i++)
    {
        m_tabLootChest[i].m_nameEquipment="no object";
        m_tabLootChest[i].m_type=other;
        m_tabLootChest[i].m_index=500;
        m_tabLootChest[i].m_isLooted=false;
        m_tabLootChest[i].m_destroyed=true;
        m_tabLootChest[i].m_dropped=false;
    }
    m_type = sbire;
    m_race = beast;
    m_xpGiving = 0;
    m_status = dead;
    m_direction = horizontalRight;
    m_waitingBeforeAttacking = 0;
}

Enemy::Enemy(EnemyType type, EnemyRace race, const Rectangle &pos,
             const Object loot, const Object tabLootChest[],
             const unsigned int health, const unsigned int level,RoamingDirection direction) :
    Character(pos,health,level)
{
    m_type = type;
    m_race = race;
    int tmpNb = rand_a_b(0,1);
    if(tmpNb == 1)
    {
        m_hasLoot = true;
        m_loot.m_nameEquipment=loot.m_nameEquipment;
        m_loot.m_type=loot.m_type;
        m_loot.m_index=500;
        m_loot.m_isLooted=false;
        m_loot.m_destroyed=false;
        m_loot.m_dropped=false;
        m_loot.m_pos = pos;
        m_loot.m_value = loot.m_value;
    }
    else
    {
        m_hasLoot = false;
    }
    if (type==boss)
    {
        m_hasChest = true;
        for(unsigned int i = 0;i<3;i++)
        {
            m_tabLootChest[i].m_nameEquipment=tabLootChest[i].m_nameEquipment;
            m_tabLootChest[i].m_type=tabLootChest[i].m_type;
            m_tabLootChest[i].m_index=500;
            m_tabLootChest[i].m_isLooted=false;
            m_tabLootChest[i].m_destroyed=false;
            m_tabLootChest[i].m_dropped=false;
            m_tabLootChest[i].m_pos = pos;
            m_tabLootChest[i].m_value = tabLootChest[i].m_value;
        }
        m_xpGiving = 1000 + (level * 100);
    }
    if(type==sbire)
    {
        m_xpGiving = 10 + (level * 5);
    }
    if(type==elite)
    {
        m_xpGiving = 100 + (level * 10);
    }
    m_status = roaming;
    m_direction = direction;
    m_posOrigin = Vec2(pos.m_position.x,pos.m_position.y);
    m_isXpGiven = true;
    m_waitingBeforeAttacking = 0;
}

void Enemy::moveRight()
{
    move(Vec2(1,0));
    updateRangeRight();
}
void Enemy::moveLeft()
{
    move(Vec2(-1,0));
    updateRangeLeft();
}
void Enemy::moveTop()
{
    move(Vec2(0,-1));
    updateRangeTop();
}
void Enemy::moveBottom()
{
    move(Vec2(0,1));
    updateRangeBottom();
}

void Enemy::enemyPattern(Player & p)
{
    int dx,dy;
    dx = m_position.m_position.x - p.getPos().m_position.x;
    dy = m_position.m_position.y - p.getPos().m_position.y;

    switch(m_status)
    {
    case roaming:
        if((abs(dx)<100)&&(abs(dy)<100))
        {
            m_status = comingToPlayer;
        }

        if(m_direction==horizontalRight)
        {
            if(m_position.m_position.x < m_posOrigin.x + 50)
            {
                moveRight();
            }
            else
            {
                m_direction=horizontalLeft;
            }
        }
        if(m_direction==horizontalLeft)
        {
            if(m_position.m_position.x > m_posOrigin.x - 50)
            {
                moveLeft();
            }
            else
            {
                m_direction=horizontalRight;
            }
        }
        if(m_direction==verticalTop)
        {
            if(m_position.m_position.y > m_posOrigin.y - 50)
            {
                moveTop();
            }
            else
            {
                m_direction=verticalBottom;
            }
        }
        if(m_direction==verticalBottom)
        {
            if(m_position.m_position.y < m_posOrigin.y + 50)
            {
                moveBottom();
            }
            else
            {
                m_direction=verticalTop;
            }
        }
        break;

    case comingToPlayer:
        if((abs(dx)>=100)||(abs(dy)>=100))
        {
            m_status = roaming;
        }
        if(p.getPos().in(m_range))
        {
            m_status = attacking;
            m_waitingBeforeAttacking = SDL_GetTicks();
        }
        if(dx<0)
        {
            moveRight();
        }
        if(dx>0)
        {
            moveLeft();
        }
        if(dy<0)
        {
            moveBottom();
        }
        if(dy>0)
        {
            moveTop();
        }
        m_posOrigin = Vec2(m_position.m_position.x,m_position.m_position.y);
        break;

    case dead:
        break;

    case attacking:
        if(!p.getPos().in(m_range))
        {
            m_status = comingToPlayer;
        }
        if((SDL_GetTicks()-m_waitingBeforeAttacking)>2000)
        {
            attack(p);
            m_waitingBeforeAttacking=SDL_GetTicks();
        }
        break;

    default:
        break;
    }
}



void Enemy::giveXp(Player &p)
{
    p.increaseXp(m_xpGiving);
}

std::string Enemy::getEnemyType() const
{
    switch(m_type)
    {

    case 0:
        return "Sbire";
    case 1:
        return "Elite";
    case 2:
        return "Boss";
    }
}

void Enemy::dropLoot()
{
    m_loot.m_dropped=true;
    m_loot.m_pos=m_position;
}

std::string Enemy::getEnemyRace() const
{
    switch(m_race)
    {

    case 0:
        return "Beast";
    case 1:
        return "Element";
    case 2:
        return "Humanoid";
    }
}

void Enemy::takeDamage(unsigned int damageToDeal,Player & player)
{
    if (damageToDeal>=m_health)
    {
        m_health = 0;
        player.kill(*this);
    }
    else
    {
        m_health -= damageToDeal;
    }
}

void Enemy::die(Player & player)
{
    std::cout<<"mort du "<<getEnemyRace()<<" "<<getEnemyType()
            <<" !"<<std::endl;
    m_alive = false;
    m_isLoaded = false;
    m_status=dead;
    giveXp(player);
    dropLoot();
}

Object Enemy::getLoot() const
{
    return m_loot;
}

Object *Enemy::getChest()
{
    return m_tabLootChest;
}

unsigned int Enemy::getTimer() const
{
    return m_waitingBeforeAttacking;
}
