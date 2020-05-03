#ifndef PLAYER_H
#define PLAYER_H

#include <string>
//#include "Inventory.h"
//#include "Equipment.h"
//#include "Consommable.h"
#include <iostream>
#include "Character.h"
class Enemy;
#include "Enemy.h"
#include "Object.h"
#include <time.h>

//structures à enlever après implémentation des classes en question

/**
 * @brief      Inventory structure
 */
struct Inventory
{
    /**
     * The equipment
     */
    Object m_tabEquip[16];

    /**
     * The number of empty slots
     */
    unsigned int m_numEmptySlot;
};

/**
 * @brief      Armor structure
 */
struct Armor
{
    /**
     * The number of defense points
     */
    unsigned int m_defense;
};

enum PlayerClass {warrior,archer,mage};

/**
 * @brief      This class describes a player.
 * 
 * This class inherits from the Character class. 
 */
class Player : public Character
{
private:
    std::string m_name;
    Object m_tabEquipped[2];
    Armor m_armor;
    PlayerClass m_class;
    unsigned int m_xpCurrent;
    unsigned int m_xpMax;
    time_t m_timer;
    void deleteObject(unsigned int index);
    //supprimer un objet et réassemble l'inventaire sans "trous"

public:

    /**
     * The player inventory
     */
    Inventory m_inventory;

    /**
     * @brief      Constructs a new instance.
     */
    Player();
    
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  name    The player name
     * @param[in]  Class   The player class
     * @param[in]  pos     The position
     * @param[in]  health  The health
     * @param[in]  level   The level
     */
    Player(const std::string & name, PlayerClass Class, const Rectangle & pos,
           const unsigned int health, const unsigned int level);

    /**
     * @brief      Gets the current xp
     *
     * @return     The current xp
     */
    unsigned int getXpCurrent() const;
    // retourne l'expérience actuelle

    /**
     * @brief      Gets the xp maximum.
     *
     * @return     The maximum xp
     */
    unsigned int getXpMax() const;
    //retourne l'xp à atteindre pour level up

    /**
     * @brief      Add xpGot to his current number of xp points
     *
     * @param[in]  xpGot  The got
     */
    void increaseXp(unsigned int xpGot);
    //gagne de l'xp : on incrémente m_xpCurrent

    /**
     * @brief      Updates the player characteristics when the player increases one level
     */
    void levelup();
    //met à jour les caractéristiques du joueur lorsqu'il level up

    /**
     * @brief      adds an object to the inventory
     *
     * @param      tabObject  The tab object
     * @param[in]  sizeTab    The size tab
     */
    void Loot(Object tabObject[],unsigned int sizeTab);
    //ajoute un objet à l'inventaire

    /**
     * @brief      The player equips himself with the object "equipement"
     *
     * @param      equipment  The equipment
     */
    void Equip(Object & equipment);
    //equipe un equipement et met l'equipement utilisé précédemment dans l'inventaire

    /**
     * @brief      Uses a consumable object 
     *
     * @param      consumable  The consumable
     */
    void Use(Object & consumable);
    //utilise un consommable

    /**
     * @brief      Opens the inventory.
     */
    void openInventory() const;
    //ouvre l'inventaire, pour l'instant juste un cout du contenu

    /**
     * @brief      Gets the name player
     *
     * @return     The name.
     */
    std::string getName() const;
    //retourne le nom du joueur

    /**
     * @brief      Gets the name class.
     *
     * @return     The name class.
     */
    std::string getNameClass() const;
    //retourne la classe du joueur sous forme de string

    /**
     * @brief      Gets the player statistics.
     */
    void getPlayerStats() const;
    //affiche les stats du joueur

    /**
     * @brief      attack the enemy
     *
     * @param      enemy  The enemy
     */
    void attack(Enemy &enemy);
    //le joueur attaque

    /**
     * @brief      inflicts damage to the enemy
     *
     * @param      enemy  The enemy
     */
    void dealDamage(Enemy & enemy);
    //inflige des dégats à l'ennemi

    /**
     * @brief      kills the enemy
     *
     * @param      enemy  The enemy
     */
    void kill(Enemy &enemy);
    //le joueur tue l'ennemi

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
     * @param[in]  copie  The player to be copied
     *
     * @return     The result of the assignment
     */
    Player& operator=(const Player &copie);

    /**
     * @brief      Sets the player health
     *
     * @param[in]  health  The health
     */
    void setHealth(const unsigned int health);
};
#endif
