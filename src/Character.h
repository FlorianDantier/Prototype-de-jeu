#ifndef CHARACTER_H
#define CHARACTER_H
//#include "Weapon.h"
#include "Image.h"

//enlever la struct Weapon après les tests
struct Weapon
{
    int m_damage;
};

class Character
{
    private:
    unsigned int m_speed;
    unsigned int m_health;
    unsigned int m_defense;
    unsigned int m_level;
    unsigned int m_strengh;
    bool m_alive;
    Rectangle m_position;
    Image m_imCharacter;

    public:
    Weapon m_weapon;
    Character(); // constructeur par défault
    Character(const Rectangle & pos, const unsigned int health, const std::string & imPath,SDL_Renderer *renderer, const unsigned int level);
    //constructeur avec pos,health et une Image en paramètre
    void move(const Vec2<int> & direction);
    //les 8 directions possibles en Vec2<int>
    Rectangle getPos() const;
    //renvoi la position sous forme de rectangle
    void setPos(const Rectangle & rec);
    //modifie la position à partir d'un rectangle
    void takeDamage(unsigned int damageToDeal);
    //reçoit des dégats et perd de la vie
    void dealDamage(Character & c_ennemi);
    // calcule les dégats infligés en fonction de l'ennemi
    unsigned int getHealth();
    //renvoi la vie du perso
    void event(const SDL_Event & event);
    //prend en compte un evènement clavier
    void display(SDL_Renderer *renderer);
    //affiche le character à l'écran
    Vec2<int> getVecPos();
    //renvoi la position sous forme de Vec2
    void die();
    //tue le personnage
    bool isAlive();
    //renvoi true si le character est vivant
    void knockBack(const SDL_Event & event);
};


#endif
