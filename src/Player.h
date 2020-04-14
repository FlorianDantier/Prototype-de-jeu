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

//structures à enlever après implémentation des classes en question

struct Inventory
{
    Object m_tabEquip[16];
    unsigned int m_numEmptySlot;
};
struct Armor
{
    unsigned int m_defense;
};

enum PlayerClass {warrior,archer,mage};

class Player : public Character
{
    private:
    std::string m_name;
    Object m_tabEquipped[2];
    Armor m_armor;
    PlayerClass m_class;
    unsigned int m_xpCurrent;
    unsigned int m_xpMax;
    clock_t m_timer;
    void deleteObject(unsigned int index);
    //supprimer un objet et réassemble l'inventaire sans "trous"

    public:
    Inventory m_inventory;

    Player();
    //constructeur par défaut
    Player(const std::string & name, PlayerClass Class, const Rectangle & pos,
           const unsigned int health, const unsigned int level);
    unsigned int getXpCurrent() const;
    // retourne l'expérience actuelle
    unsigned int getXpMax() const;
    //retourne l'xp à atteindre pour level up
    void increaseXp(unsigned int xpGot);
    //gagne de l'xp : on incrémente m_xpCurrent
    void levelup();
    //met à jour les caractéristiques du joueur lorsqu'il level up
    void Loot(Object tabObject[],unsigned int sizeTab);
    //ajoute un objet à l'inventaire
    void Equip(Object & equipment);
    //equipe un equipement et met l'equipement utilisé précédemment dans l'inventaire
    void Use(Object & consumable);
    //utilise un consommable
    void openInventory() const;
    //ouvre l'inventaire, pour l'instant juste un cout du contenu
    std::string getName() const;
    //retourne le nom du joueur
    std::string getNameClass() const;
    //retourne la classe du joueur sous forme de string
    void getPlayerStats() const;
    //affiche les stats du joueur
    void attack(Enemy &enemy);
    //le joueur attaque
    void dealDamage(Enemy & enemy);
    //inflige des dégats à l'ennemi
    void kill(Enemy &enemy);
    //le joueur tue l'ennemi
    unsigned int getTimer() const;
    //retourne le temps de la dernière attaque
};
#endif
