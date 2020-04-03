#ifndef PLAYER_H
#define PLAYER_H

#include <string>
//#include "Inventory.h"
//#include "Equipment.h"
//#include "Consommable.h"
#include "Character.h"
#include <iostream>

//structures à enlever après implémentation des classes en question
enum ObjectType {weapon,armor,other};
struct Object
{
    std::string m_nameEquipment;
    ObjectType m_type;
    unsigned int m_index;
    Rectangle m_pos;
    Image m_image;
    bool m_isLooted;
    int m_value;
    bool m_destroyed;
};
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
    void deleteObject(unsigned int index);
    //supprimer un objet et réassemble l'inventaire sans "trous"

    public:
    Inventory m_inventory;

    Player();
    Player(const std::string & name,PlayerClass Class,const Rectangle & pos,
           const unsigned int health,const unsigned int level,
           const std::string & imPath,SDL_Renderer *renderer);
    unsigned int getXpCurrent() const;
    // retourne l'expérience actuelle
    unsigned int getXpMax() const;
    //retourne l'xp à atteindre pour level up
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
};
#endif
