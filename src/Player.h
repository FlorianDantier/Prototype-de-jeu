#include <string.h>
#include "Inventory.h"
#include "Equipment.h"

enum PlayerClass {warrior,archer,mage};

class Player
{
    private:
    string m_name;
    unsigned int m_intelligence;
    unsigned int m_agility;
    unsigned int m_mana;
    Inventory m_inventory;
    Armor m_armor;
    PlayerClass m_class;

    public:
    Player();
    Player(const & string name, PlayerClass Class);
    void Loot(Object & object);
    void Equip(Equipment & equipment);
}