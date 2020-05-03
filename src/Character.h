#ifndef CHARACTER_H
#define CHARACTER_H
//#include "Weapon.h"
#include "Image.h"
#include <vector>
#include <ctime>

//enlever la struct Weapon après la création de la classe Weapon

/**
 * @brief      The character orientation
 */
enum Orientation
{
    north = 0,
    west,
    south,
    east,
};



/**
 * @brief      Weapon structure
 */
struct Weapon
{
    /**
     * damage points
     */
    int m_damage;
};

/**
 * @brief      This class describes a character.
 * 
 * For example, a character can be a player or an enemy
 */
class Character
{
protected:
    unsigned int m_health;
    unsigned int m_maxHealth;
    unsigned int m_defense;
    unsigned int m_level;
    unsigned int m_strengh;
    bool m_alive;
    Rectangle * m_position;
    Rectangle * m_range;
    bool m_isLoaded;
    bool m_isXpGiven;
    Orientation m_orient;

public:
    /**
     * the character weapon
     */
    Weapon m_weapon;

    /**
     * @brief      Constructs a new instance.
     */
    Character(); // constructeur par défault
    
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  pos     The character position
     * @param[in]  health  The character health
     * @param[in]  level   The character level
     */
    Character(const Rectangle &pos, const unsigned int health,
              const unsigned int level);
    //constructeur avec pos,health,level en paramètre

    /**
     * @brief      Destroys the object.
     */
    ~Character();

    /**
     * @brief      this character moves in one direction
     *
     * @param[in]  direction  The character direction
     */
    void move(const Vec2<int> & direction);
    //les 8 directions possibles en Vec2<int>

    /**
     * @brief      Gets the position.
     *
     * @return     The position.
     */
    Rectangle& getPos() const;
    //renvoi la position sous forme de rectangle

    /**
     * @brief      Sets the character position.
     *
     * @param[in]  rec   The new value
     */
    void setPos(const Rectangle & rec);
    //modifie la position à partir d'un rectangle

    /**
     * @brief      The character takes damage
     *
     * @param[in]  damageToDeal  The damage points to deal
     * @param      enemy         A reference to the enemy
     */
    void takeDamage(unsigned int damageToDeal,Character & enemy);
    //reçoit des dégats et perd de la vie

    /**
     * @brief      calculates the damage inflicted according to the enemy and inflicts damage if within range 
     *
     * @param      c_ennemi  The c ennemi
     */
    void dealDamage(Character & c_ennemi);
    // calcule les dégats infligés en fonction de l'ennemi et inflige des dégats s'il est à portée

    /**
     * @brief      Gets the character health.
     *
     * @return     The character health.
     */
    unsigned int getHealth() const;
    // retourne la vie du character

    /**
     * @brief      Gets the maximum character health.
     *
     * @return     The maximum character health.
     */
    unsigned int getMaxHealth() const;
    //retourne la vie maximale du character

    /**
     * @brief      Gets the character level.
     *
     * @return     The character level.
     */
    unsigned int getLevel() const;
    // retourne son level

    /**
     * @brief      Gets the character defense.
     *
     * @return     The character defense.
     */
    unsigned int getDefense() const;
    // retourne sa défense

    /**
     * @brief      Gets the strengh.
     *
     * @return     The strengh.
     */
    unsigned int getStrengh() const;
    // retourne sa force d'attaque physique

    /**
     * @brief      Gets the character range.
     *
     * @return     The character range.
     */
    Rectangle& getRange() const;
    //retourne sa portée sous forme de rectangle

    /**
     * @brief      Sets the character health.
     *
     * @param[in]  health  The health
     */
    void setHealth(const unsigned int health);
    //modifie la vie

    /**
     * @brief      Sets the maximum character health.
     *
     * @param[in]  maxHealth  The maximum character health
     */
    void setMaxHealth(const unsigned int maxHealth);
    //modifie la vie maximale

    /**
     * @brief      Sets the character level.
     *
     * @param[in]  level  The character level
     */
    void setLevel(const unsigned int level);
    //modifie le level

    /**
     * @brief      Sets the character defense.
     *
     * @param[in]  defense  The character defense
     */
    void setDefense(const unsigned int defense);
    //modifie la défense

    /**
     * @brief      Sets the character strengh.
     *
     * @param[in]  strengh  The character strengh
     */
    void setStrengh(const unsigned int strengh);
    //modifie la force d'attaque physique

    /**
     * @brief      Sets the character range.
     *
     * @param      range  The character range
     */
    void setRange(Rectangle *range);
    //modifie le rectangle de la portée

    /**
     * @brief      The character moves to the right and manage all the updates
     *
     * @param      tabCharacter  The array of characters
     * @param[in]  sizeTab       The size of the array
     */
    void updatePlayerMoveRight(Character tabCharacter[],unsigned int sizeTab);
    //le joueur bouge à droite + gestion de toutes les mise à jour suite à cette action

    /**
     * @brief      The character moves to the left and manage all the updates
     *
     * @param      tabCharacter  The array of characters
     * @param[in]  sizeTab       The size of the array
     */
    void updatePlayerMoveLeft(Character tabCharacter[],unsigned int sizeTab);
    //le joueur bouge à droite + gestion de toutes les mise à jour suite à cette action

    /**
     * @brief      The character moves up and manage all the updates
     *
     * @param      tabCharacter  The array of characters
     * @param[in]  sizeTab       The size of the array
     */
    void updatePlayerMoveTop(Character tabCharacter[],unsigned int sizeTab);
    //le joueur bouge à droite + gestion de toutes les mise à jour suite à cette action

    /**
     * @brief      The character moves down and manage all the updates
     *
     * @param      tabCharacter  The array of characters
     * @param[in]  sizeTab       The size of the array
     */
    void updatePlayerMoveBottom(Character tabCharacter[],unsigned int sizeTab);
    //le joueur bouge à droite + gestion de toutes les mise à jour suite à cette action

    /**
     * @brief      Displays the object.
     */
    void display();
    //affiche le character à l'écran

    /**
     * @brief      Gets the vector position.
     *
     * @return     The vector position.
     */
    Vec2<int> getVecPos();
    //renvoi la position sous forme de Vec2

    /**
     * @brief      This character die
     */
    void die();
    //tue le personnage

    /**
     * @brief      Determines if the character is alive.
     *
     * @return     True if alive, False otherwise.
     */
    bool isAlive() const;
    //renvoi true si le character est vivant

    /**
     * @brief      pushes back to the right
     */
    void knockBackRight();
    //repousse vers la droite

    /**
     * @brief      Pushes back to the left
     */
    void knockBackLeft();
    //repousse vers la gauche

    /**
     * @brief      Pushes back up
     */
    void knockBackTop();
    //repousse vers le haut

    /**
     * @brief      Pushes back down
     */
    void knockBackBottom();
    //repousse vers le bas

    /**
     * @brief      Kills an enemy
     *
     * @param      enemy  The enemy
     */
    void kill(Character & enemy);
    //tue une entité quand sa vie est à 0

    /**
     * @brief      Attacks an enemy
     *
     * @param      enemy  The enemy
     */
    void attack(Character & enemy);
    //attaque lorsque la touche d'attaque est enfoncée

    /**
     * @brief      Scope update on the right
     */
    void updateRangeRight();
    //mise à jour de la portée à droite

    /**
     * @brief      Scope update on the left
     */
    void updateRangeLeft();
    //mise à jour de la portée à gauche

    /**
     * @brief      Scope update up
     */
    void updateRangeTop();
    //mise à jour de la portée en haut

    /**
     * @brief      Scope update down
     */
    void updateRangeBottom();
    //mise à jour de la portée en bas

    /**
     * @brief      collides with an enemy, loses life and is pushed back to the left.
     *
     * @param      tabCharacter  The array of characters
     * @param[in]  sizeTab       The size of the array
     */
    void crashWithEnemyOnRight(Character tabCharacter[],unsigned int sizeTab);
    // collision avec un ennemi, perd de la vie et est repoussé vers la gauche

    /**
     * @brief      collides with an enemy, loses life and is pushed back to the right.
     *
     * @param      tabCharacter  The array of characters
     * @param[in]  sizeTab       The size of the array
     */
    void crashWithEnemyOnLeft(Character tabCharacter[],unsigned int sizeTab);
    // collision avec un ennemi, perd de la vie et est repoussé vers la droite

    /**
     * @brief      collides with an enemy, loses life and is pushed back down.
     *
     * @param      tabCharacter  The array of characters
     * @param[in]  sizeTab       The size of the array
     */
    void crashWithEnemyOnBottom(Character tabCharacter[],unsigned int sizeTab);
    // collision avec un ennemi, perd de la vie et est repoussé vers le haut

    /**
     * @brief      collides with an enemy, loses life and is pushed back up
     *
     * @param      tabCharacter  The array of characters
     * @param[in]  sizeTab       The size of the array
     */
    void crashWithEnemyOnTop(Character tabCharacter[],unsigned int sizeTab);
    // collision avec un ennemi, perd de la vie et est repoussé vers le bas

    /**
     * @brief      Sets the characters as loaded or not
     *
     * @param[in]  load  A boolean
     */
    void setLoaded(bool load);
    // charge ou décharge l'entité

    /**
     * @brief      Determines if loaded.
     *
     * @return     True if loaded, False otherwise.
     */
    bool isLoaded() const;
    // retour si l'entité est chargée

    /**
     * @brief      Tests the inputs and outputs
     *
     * @return     A boolean
     */
    bool testInOut();
    //vérifie que le character ne sort pas de l'écran

    /**
     * @brief      Sets the character orientation.
     *
     * @param[in]  orient  The character orientation
     */
    void setOrientation(const Orientation orient);

    /**
     * @brief      Gets the character orientation.
     *
     * @return     The character orientation.
     */
    Orientation getOrientation() const;

    /**
     * @brief      Assignment operator.
     *
     * @param[in]  copie  The character to be copied
     *
     * @return     The result of the assignment
     */
    Character& operator=(const Character &copie);
};


#endif
