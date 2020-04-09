#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"
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
    Object m_tabLoot[5];
    bool m_hasChest;
    Object m_tabLootChest[5];
    EnemyType m_type;
    EnemyRace m_race;
    unsigned int m_xpGiving;
    EnemyStatus m_status;
    RoamingDirection m_direction;
    clock_t m_timer;
    Vec2<int> m_posOrigin;

public:
    Enemy();
    //constructeur par défaut
    Enemy(EnemyType type, EnemyRace race, const Rectangle & pos, const Object tabLoot[], const Object tabLootChest[],
          const unsigned int health, const unsigned int level,
          const std::string & imPath,RoamingDirection direction, SDL_Renderer *renderer);

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
};

#endif // ENEMY_H
