#include "Enemy.h"
#include <math.h>
#include "common.h"


// On suppose a<b
int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

Enemy::Enemy()
{
    m_hasLoot = false;
    //m_loot = Object();
    m_hasChest = false;
    //m_Chest = Object();
    m_type = sbire;
    m_race = beast;
    m_xpGiving = 0;
    m_status = dead;
    m_direction = horizontalRight;
    m_waitingBeforeAttacking = 0;
    m_posOrigin = nullptr;
    m_soundDeath = false;
}

Enemy::Enemy(EnemyType type, EnemyRace race, const Rectangle &pos,
             /*Object loot, Object Chest,*/
             const unsigned int health, const unsigned int level,
             RoamingDirection direction, bool hasLoot) :
    Character(pos,health,level)
{
    m_type = type;
    m_race = race;
    if(hasLoot)
    {
        m_hasLoot = true;
       /* m_loot = loot;
        m_loot.setDropped(false);*/
    }
    else
    {
        m_hasLoot = false;
    }
    if (type==boss)
    {
        m_hasChest = true;
       /* m_Chest = Chest;
        m_Chest.setDropped(false);*/
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
    delete m_posOrigin;
    m_posOrigin = new Vec2<int>(pos.m_position.x,pos.m_position.y);
    std::cout<<"position enemy :"<<pos.m_position.x<<","
            <<pos.m_position.y<<std::endl;
    std::cout<<"position enemy :"<<m_posOrigin->x<<","
            <<m_posOrigin->y<<std::endl;
    m_isXpGiven = true;
    m_waitingBeforeAttacking = 0;
    m_soundDeath = false;
}

void Enemy::moveRight()
{
    move(Vec2<int>(2,0));
    updateRangeRight();
}
void Enemy::moveLeft()
{
    move(Vec2<int>(-2,0));
    updateRangeLeft();
}
void Enemy::moveTop()
{
    move(Vec2<int>(0,-2));
    updateRangeTop();
}
void Enemy::moveBottom()
{
    move(Vec2<int>(0,2));
    updateRangeBottom();
}

void Enemy::enemyPattern(Player & p)
{
    int dx,dy;
    dx = m_position->m_position.x - p.getPos().m_position.x;
    dy = m_position->m_position.y - p.getPos().m_position.y;

    switch(m_status)
    {
    case roaming:
        if((abs(dx)<100)&&(abs(dy)<100))
        {
            m_status = comingToPlayer;
        }

        if(m_direction==horizontalRight)
        {
            if(m_position->m_position.x < m_posOrigin->x + 50)
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
            if(m_position->m_position.x > m_posOrigin->x - 50)
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
            if(m_position->m_position.y > m_posOrigin->y - 50)
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
            if(m_position->m_position.y < m_posOrigin->y + 50)
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
            delete m_posOrigin;
            m_posOrigin = new Vec2<int>(m_position->m_position.x,
                                        m_position->m_position.y);
        }
        if(p.getPos().in(*(m_range)))
        {
            m_status = attacking;
            m_waitingBeforeAttacking = time(NULL);
                    //SDL_GetTicks();
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
        break;

    case dead:
        break;

    case attacking:
        if(!p.getPos().in(*(m_range)))
        {
            m_status = comingToPlayer;
        }
        if((time(NULL)-m_waitingBeforeAttacking) > 2)
        {
            attack(p);
            m_waitingBeforeAttacking=time(NULL);
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
    default:
        return "error";
    }
}

void Enemy::dropLoot()
{
   /* m_loot.setDropped(true);
    m_loot.setPos(*m_position);
    m_Chest.setDropped(true);
    m_Chest.setPos(*m_position);*/
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
    default:
        return "error";
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
    m_soundDeath=true;
    //dropLoot();
}

/*Object Enemy::getLoot() const
{
    return m_loot;
}

Object Enemy::getChest()
{
    return m_Chest;
}*/

time_t Enemy::getTimer() const
{
    return m_waitingBeforeAttacking;
}

Enemy &Enemy::operator=(const Enemy &copie)
{
    if(this != &copie)
    {
        m_type = copie.m_type;
        m_race = copie.m_race;
        if(copie.m_hasLoot)
        {
            m_hasLoot = true;
           /* m_loot = loot;
            m_loot.setDropped(false);*/
        }
        else
        {
            m_hasLoot = false;
        }
        if (copie.m_type==boss)
        {
            m_hasChest = true;
           /* m_Chest = Chest;
            m_Chest.setDropped(false);*/
            m_xpGiving = 1000 + (copie.m_level * 100);
        }
        if(copie.m_type==sbire)
        {
            m_xpGiving = 10 + (copie.m_level * 5);
        }
        if(copie.m_type==elite)
        {
            m_xpGiving = 100 + (copie.m_level * 10);
        }
        m_status = roaming;
        m_direction = copie.m_direction;
        delete m_posOrigin;
        m_posOrigin = new Vec2<int>(*(copie.m_posOrigin));
        m_isXpGiven = true;
        m_waitingBeforeAttacking = 0;
    }
    return *this;
}

bool Enemy::getSoundDeath() const
{
    return m_soundDeath;
}

void Enemy::setSoundDeath(const bool emitSoundDeath)
{
    m_soundDeath = emitSoundDeath;
}
