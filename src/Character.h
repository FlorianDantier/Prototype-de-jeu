#ifndef CHARACTER_H
#define CHARACTER_H
//#include "Weapon.h"
#include "Image.h"

//enlever la struct Weapon après la création de la classe Weapon
struct Weapon
{
    int m_damage;
};

class Character
{
    protected:
    unsigned int m_health;
    unsigned int m_maxHealth;
    unsigned int m_defense;
    unsigned int m_level;
    unsigned int m_strengh;
    bool m_alive;
    Rectangle m_position;
    Rectangle m_range;
    Image m_imCharacter;
    bool m_isLoaded;

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
    void takeDamage(unsigned int damageToDeal,Character & enemy);
    //reçoit des dégats et perd de la vie
    void dealDamage(Character & c_ennemi);
    // calcule les dégats infligés en fonction de l'ennemi et inflige des dégats s'il est à portée
    unsigned int getHealth();
    // retourne la vie du character
    unsigned int getMaxHealth();
    //retourne la vie maximale du character
    unsigned int getLevel();
    // retourne son level
    unsigned int getDefense();
    // retourne sa défense
    unsigned int getStrengh();
    // retourne sa force d'attaque physique
    Rectangle getRange() const;
    //retourne sa portée sous forme de rectangle
    void setHealth(const unsigned int health);
    //modifie la vie
    void setMaxHealth(const unsigned int maxHealth);
    //modifie la vie maximale
    void setLevel(const unsigned int level);
    //modifie le level
    void setDefense(const unsigned int defense);
    //modifie la défense
    void setStrengh(const unsigned int strengh);
    //modifie la force d'attaque physique
    void setRange(const Rectangle & range);
    //modifie le rectangle de la portée
    void event(const SDL_Event & event,Character tabCharacter[]);
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
    // repousse quand touché
    void kill(Character & enemy);
    //tue une entité quand sa vie est à 0
    void attack(Character & enemy);
    //attaque lorsque la touche d'attaque est enfoncée
    void updateRange(const SDL_Event & event);
    //mise à jour de la portée
    void crashWithEnemy(Character tabCharacter[],const SDL_Event &event);
    // collision avec un ennemi, perd de la vie et est repoussé
    void setLoaded(bool load);
    // charge ou décharge l'entité
    bool isLoaded();
    // retour si l'entité est chargée
};


#endif
