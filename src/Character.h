#ifndef CHARACTER_H
#define CHARACTER_H
#include "Rectangle.h"
#include "Vec2.h"
#include "Weapon.h"
#include "Image.h"

class Character
{
    private:
    Vec2<int> m_position;
    unsigned int m_speed;
    unsigned int m_health;
    unsigned int m_defense;
    unsigned int m_level;
    unsigned int m_strengh;
    Weapon m_weapon;
    Image m_imCharacter;

    public:
    Character(); // constructeur par défault
    Character(const & Vec2 pos, unsigned int health, const & Image imChar);
    //constructeur avec pos,health et une Image en paramètre
    void move(Vec2<int> direction);
    //les 8 directions possibles en Vec2<int>
    Rectangle getPos() const;
    //renvoi la position sous forme de rectangle
    void setPos(const & Rectangle rec);
    //modifie la position à partir d'un rectangle
    void dealDamage(Character & c_ennemi);
    // calcule les dégats infligés en fonction de l'ennemi
}


#endif