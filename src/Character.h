#ifndef CHARACTER_H
#define CHARACTER_H
//#include "Weapon.h"
#include "Image.h"
#include <vector>
#include <ctime>

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
    bool m_isLoaded;
    bool m_isXpGiven;

    public:
    Weapon m_weapon;
    Character(); // constructeur par défault
    Character(const Rectangle & pos, const unsigned int health,
              const unsigned int level);
    //constructeur avec pos,health,level en paramètre
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
    unsigned int getHealth() const;
    // retourne la vie du character
    unsigned int getMaxHealth() const;
    //retourne la vie maximale du character
    unsigned int getLevel() const;
    // retourne son level
    unsigned int getDefense() const;
    // retourne sa défense
    unsigned int getStrengh() const;
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
    void updatePlayerMoveRight(Character tabCharacter[],unsigned int sizeTab);
    //le joueur bouge à droite + gestion de toutes les mise à jour suite à cette action
    void updatePlayerMoveLeft(Character tabCharacter[],unsigned int sizeTab);
    //le joueur bouge à droite + gestion de toutes les mise à jour suite à cette action
    void updatePlayerMoveTop(Character tabCharacter[],unsigned int sizeTab);
    //le joueur bouge à droite + gestion de toutes les mise à jour suite à cette action
    void updatePlayerMoveBottom(Character tabCharacter[],unsigned int sizeTab);
    //le joueur bouge à droite + gestion de toutes les mise à jour suite à cette action
    void display();
    //affiche le character à l'écran
    Vec2<int> getVecPos();
    //renvoi la position sous forme de Vec2
    void die();
    //tue le personnage
    bool isAlive() const;
    //renvoi true si le character est vivant
    void knockBackRight();
    //repousse vers la droite
    void knockBackLeft();
    //repousse vers la gauche
    void knockBackTop();
    //repousse vers le haut
    void knockBackBottom();
    //repousse vers le bas
    void kill(Character & enemy);
    //tue une entité quand sa vie est à 0
    void attack(Character & enemy);
    //attaque lorsque la touche d'attaque est enfoncée
    void updateRangeRight();
    //mise à jour de la portée à droite
    void updateRangeLeft();
    //mise à jour de la portée à gauche
    void updateRangeTop();
    //mise à jour de la portée en haut
    void updateRangeBottom();
    //mise à jour de la portée en bas
    void crashWithEnemyOnRight(Character tabCharacter[],unsigned int sizeTab);
    // collision avec un ennemi, perd de la vie et est repoussé vers la gauche
    void crashWithEnemyOnLeft(Character tabCharacter[],unsigned int sizeTab);
    // collision avec un ennemi, perd de la vie et est repoussé vers la droite
    void crashWithEnemyOnBottom(Character tabCharacter[],unsigned int sizeTab);
    // collision avec un ennemi, perd de la vie et est repoussé vers le haut
    void crashWithEnemyOnTop(Character tabCharacter[],unsigned int sizeTab);
    // collision avec un ennemi, perd de la vie et est repoussé vers le bas
    void setLoaded(bool load);
    // charge ou décharge l'entité
    bool isLoaded() const;
    // retour si l'entité est chargée
    bool testInOut();
    //vérifie que le character ne sort pas de l'écran
};


#endif
