#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"
class Player;
#include "Player.h"
#include "Object.h"
#include <time.h>


enum EnemyType {sbire,elite,boss};
enum EnemyRace {beast,element,humanoid};
enum EnemyStatus {roaming,comingToPlayer,attacking,dead};
enum RoamingDirection
{
    verticalTop,
    verticalBottom,
    horizontalRight,
    horizontalLeft
};

/**
 * @brief      This class describes an enemy.
 *
 * This class inherits from the Character class.
 */
class Enemy : public Character
{
private:
    bool m_hasLoot;
    //Object m_loot;
    bool m_hasChest;
    //Object m_Chest;
    EnemyType m_type;
    EnemyRace m_race;
    unsigned int m_xpGiving;
    EnemyStatus m_status;
    RoamingDirection m_direction;
    Vec2<int> * m_posOrigin;
    time_t m_waitingBeforeAttacking;
    bool m_soundDeath;

public:
    /**
     * @brief      Constructs a new instance.
     */
    Enemy();
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  type       The enemy type
     * @param[in]  race       The enemy race
     * @param[in]  pos        The position
     * @param[in]  health     The health
     * @param[in]  level      The level
     * @param[in]  direction  The spawn direction
     * @param[in]  hasLoot    Indicates if the enemy has loot
     */
    Enemy(EnemyType type, EnemyRace race, const Rectangle & pos,
          /*Object loot, Object Chest,*/
          const unsigned int health, const unsigned int level,
          RoamingDirection direction, bool hasLoot);

    /**
     * @brief      moves this enemy to the right
     */
    void moveRight();
    /**
     * @brief      moves this enemy to the left
     */
    void moveLeft();
    /**
     * @brief      moves this enemy up
     */
    void moveTop();
    /**
     * @brief      moves this enemy down
     */
    void moveBottom();
    /**
     * @brief      Artificial intelligence
     *
     * @param      p     { parameter_description }
     */
    void enemyPattern(Player &p);
    //implantation de l'IA des monstres (rudimentaire)
    //roaming,attacking,comingToPlayer
    
    /**
     * @brief      Gives xp to the player
     *
     * @param      p     the player
     */
    void giveXp(Player & p);
    //mort de l'ennemi = donner l'expérience au joueur et faire tomber le loot s'ily en a

    /**
     * @brief      Gets the enemy race.
     *
     * @return     The enemy race
     */
    std::string getEnemyRace() const;
    //retourne la race de l'ennemi sous forme de string

    /**
     * @brief      Gets the enemy type.
     *
     * @return     The enemy type.
     */
    std::string getEnemyType() const;
    //retourne le type de l'ennemi sous forme de string

    /**
     * @brief      Drops Loot after his death if he has
     */
    void dropLoot();
    //fait tomber le loot après la mort s'il avait du loot

    /**
     * @brief      This enemy takes damage
     *
     * @param[in]  damageToDeal  The damage to deal
     * @param      player        The player
     */
    void takeDamage(unsigned int damageToDeal, Player &player);
    //l'ennemi reçoit des dégats

    /**
     * @brief      The enemy dies
     *
     * @param      player  The player
     */
    void die(Player &player);
    //tue l'ennemi

    /**
     * @brief      Gets the loot of this enemy
     *
     * @return     The loot.
     */
    Object getLoot() const;
    //retourne le loot

    /**
     * @brief      Gets the chest.
     *
     * @return     The chest.
     */
    Object getChest();
    //retourne le loot dans le coffre du boss

    /**
     * @brief      Gets the timer.
     *
     * @return     The timer.
     */
    time_t getTimer() const;
    //retourne le temps de la dernière attaque

    /**
     * @brief      Assignment operator.
     *
     * @param[in]  copie  The copie
     *
     * @return     The result of the assignment
     */
    Enemy& operator=(const Enemy &copie);

    /**
     * @brief      Returns true if the enemy is death
     *
     * @return     a boolean
     */
    bool getSoundDeath() const;
    //retourne s'il on doit émetter le son de mort de l'ennemi

    /**
     * @brief      Sets EmitSoundDeath to true in order to emit a sound death
     *
     * @param[in]  EmitSoundDeath  A boolean
     */
    void setSoundDeath(const bool EmitSoundDeath);
};

#endif // ENEMY_H
