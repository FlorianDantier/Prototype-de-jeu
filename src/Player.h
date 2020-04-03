#ifndef PLAYER_H
#define PLAYER_H

#include <string>
//#include "Inventory.h"
//#include "Equipment.h"
#include "Character.h"
#include <iostream>

//structures à enlever après implémentation des classes en question
enum EquipmentType {weapon,armor,other};
struct Equipment
{
    std::string m_nameEquipment;
    EquipmentType m_type;
    unsigned int m_index;
    Rectangle m_pos;
    Image m_image;
    bool m_isLooted;
};
struct Inventory
{
    Equipment m_tabEquip[16];
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
    Inventory m_inventory;
    Equipment m_tabEquipped[2];
    Armor m_armor;
    PlayerClass m_class;
    unsigned int m_xpCurrent;
    unsigned int m_xpMax;

    public:
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
    void Loot(Equipment tabObject[],unsigned int sizeTab);
    //ajoute un objet à l'inventaire
    void Equip(Equipment & equipment);
    //equipe un equipement et met l'equipement utilisé précédemment dans l'inventaire
    void event(Character tabCharacter[], Equipment tabObject[]);
    //gère les évènements clavier et collisions du joueur etc
    void openInventory() const;
    //ouvre l'inventaire, pour l'instant juste un cout du contenu
};
#endif
