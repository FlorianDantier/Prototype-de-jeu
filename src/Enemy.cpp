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
    for(unsigned int i = 0;i<3;i++)
    {
        m_tabLoot[i].m_nameEquipment="no object";
        m_tabLoot[i].m_type=other;
        m_tabLoot[i].m_index=500;
        m_tabLoot[i].m_isLooted=true;
        m_tabLoot[i].m_destroyed=true;
        m_tabLoot[i].m_dropped=false;
    }
    m_hasChest = false;
    for(unsigned int i = 0;i<5;i++)
    {
        m_tabLootChest[i].m_nameEquipment="no object";
        m_tabLootChest[i].m_type=other;
        m_tabLootChest[i].m_index=500;
        m_tabLootChest[i].m_isLooted=true;
        m_tabLootChest[i].m_destroyed=false;
        m_tabLootChest[i].m_dropped=false;
    }
    m_type = sbire;
    m_race = beast;
    m_xpGiving = 0;
    m_status = dead;
    m_direction = horizontalRight;
    m_timer = clock();
}

Enemy::Enemy(EnemyType type, EnemyRace race, const Rectangle &pos,
             const Object tabLoot[], const Object tabLootChest[],
             const unsigned int health, const unsigned int level,RoamingDirection direction) :
    Character(pos,health,level)
{
    m_type = type;
    m_race = race;
    int tmpNb = rand_a_b(0,1);
    if(tmpNb == 1)
    {
        m_hasLoot = true;
        for(unsigned int i = 0;i<3;i++)
        {
            m_tabLoot[i].m_nameEquipment=tabLoot[i].m_nameEquipment;
            m_tabLoot[i].m_type=tabLoot[i].m_type;
            m_tabLoot[i].m_index=500;
            m_tabLoot[i].m_isLooted=false;
            m_tabLoot[i].m_destroyed=false;
            m_tabLoot[i].m_dropped=false;
            m_tabLoot[i].m_pos = pos;
            m_tabLoot[i].m_image = tabLoot[i].m_image;
            m_tabLoot[i].m_value = tabLoot[i].m_value;
        }
    }
    else
    {
        m_hasLoot = false;
    }
    if (type==boss)
    {
        m_hasChest = true;
        for(unsigned int i = 0;i<5;i++)
        {
            m_tabLootChest[i].m_nameEquipment=tabLootChest[i].m_nameEquipment;
            m_tabLootChest[i].m_type=tabLootChest[i].m_type;
            m_tabLootChest[i].m_index=500;
            m_tabLootChest[i].m_isLooted=false;
            m_tabLootChest[i].m_destroyed=false;
            m_tabLootChest[i].m_dropped=false;
            m_tabLootChest[i].m_pos = pos;
            m_tabLootChest[i].m_image = tabLootChest[i].m_image;
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
    m_timer = clock();
    m_posOrigin = Vec2(pos.m_position.x,pos.m_position.y);
    m_isXpGiven = true;
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
        if(((clock()-m_timer)/CLOCKS_PER_SEC)>2)
        {
            attack(p);
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
