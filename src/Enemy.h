#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"
class Player;
#include "Player.h"
#include "Object.h"


enum EnemyType {sbire,elite,boss};
enum EnemyRace {beast,element,humanoid};
enum EnemyStatus {roaming,comingToPlayer,attacking,dead};
enum RoamingDirection {verticalTop,verticalBottom,horizontalRight,horizontalLeft};


class Enemy : public Character
{
private:
    bool m_hasLoot;
    Object m_loot;
    bool m_hasChest;
    Object m_tabLootChest[3];
    EnemyType m_type;
    EnemyRace m_race;
    unsigned int m_xpGiving;
    EnemyStatus m_status;
    RoamingDirection m_direction;
    Vec2<int> m_posOrigin;
    unsigned int m_waitingBeforeAttacking;

public:
    Enemy();
    //constructeur par défaut
    Enemy(EnemyType type, EnemyRace race, const Rectangle & pos, const Object loot, const Object tabLootChest[],
          const unsigned int health, const unsigned int level, RoamingDirection direction);

    void moveRight();
    // va à droite
    void moveLeft();
    // va à gauche
    void moveTop();
    // va en haut
    void moveBottom();
    // va en bas
    void enemyPattern(Player &p);
    //implantation de l'IA des monstres (rudimentaire) //roaming,attacking,comingToPlayer
    void giveXp(Player & p);
    //mort de l'ennemi = donner l'expérience au joueur et faire tomber le loot s'ily en a
    std::string getEnemyRace() const;
    //retourne la race de l'ennemi sous forme de string
    std::string getEnemyType() const;
    //retourne le type de l'ennemi sous forme de string
    void dropLoot();
    //fait tomber le loot après la mort s'il avait du loot
    void takeDamage(unsigned int damageToDeal, Player &player);
    //l'ennemi reçoit des dégats
    void die(Player &player);
    //tue l'ennemi
    Object getLoot() const;
    //retourne le loot
    Object * getChest();
    //retourne le loot dans le coffre du boss
    unsigned int getTimer() const;
    //retourne le temps de la dernière attaque
};

#endif // ENEMY_H
