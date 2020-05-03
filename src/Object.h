#ifndef OBJECT_H
#define OBJECT_H

#include "Image.h"
#include <string>

/**
 * @brief      Enumeration of the object type
 */
enum ObjectType {weapon,armor,other};

/**
 * @brief      This class describes an object.
 */
class Object
{
protected:
    std::string m_nameObject;
    ObjectType m_type;
    unsigned int m_index;
    Rectangle *m_pos;
    bool m_isLooted;
    int m_value;
    bool m_isDestroyed;
    bool m_isDropped;

public:
    /**
     * @brief      Constructs a new instance.
     */
    Object();
    //constructeur par défaut

    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  name     The object name
     * @param[in]  type     The object type
     * @param[in]  index    The object index
     * @param[in]  pos      The object position
     * @param[in]  value    The object value
     * @param[in]  looted   Indicates if looted
     * @param[in]  dropped  Indicates if dropped
     */
    Object(const std::string & name,ObjectType type,unsigned int index,
           const Rectangle & pos,int value,bool looted,bool dropped);
    //constructeur prenant en paramètre le nom, le type, l'indice,
    //la position et le bonus de l'objet
    //Object(const Object &copie);
    //contructeur par copie
    
    /**
     * @brief      Destroys the object.
     */
    ~Object();
    //destructeur

    /**
     * @brief      Gets the object name.
     *
     * @return     The object name
     */
    std::string getNameObject() const;
    //retourne le nom de l'objet

    /**
     * @brief      Gets the object type.
     *
     * @return     The object type
     */
    ObjectType getType() const;
    //retourne le type d'objet

    /**
     * @brief      Gets the object index.
     *
     * @return     The object index.
     */
    unsigned int getIndex() const;
    //retourne l'indice de l'objet

    /**
     * @brief      Gets the object position.
     *
     * @return     The object position.
     */
    Rectangle& getPos() const;
    //retourne la position sous forme de rectangle

    /**
     * @brief      Determines if looted.
     *
     * @return     True if looted, False otherwise.
     */
    bool isLooted() const;
    // retourne vrai si l'objet est loot

    /**
     * @brief      Gets the value of the object bonus
     *
     * @return     The bonus value
     */
    int getValue() const;
    //retourne la valeur du bonus de l'objet

    /**
     * @brief      Determines if destroyed.
     *
     * @return     True if destroyed, False otherwise.
     */
    bool isDestroyed() const;
    //retourne vrai si l'objet est détruit/à détruire

    /**
     * @brief      Determines if dropped.
     *
     * @return     True if dropped, False otherwise.
     */
    bool isDropped() const;
    //retourne vrai si l'objet a été laissé tombé (par un monstre)

    /**
     * @brief      Sets the looted boolean.
     *
     * @param[in]  looted  Indicates if looted or not
     */
    void setLooted(bool looted);
    //modifie le booléen est loot

    /**
     * @brief      Sets the destroyed boolean
     *
     * @param[in]  destroyed  Indicates if destroyed or nit
     */
    void setDestroyed(bool destroyed);
    //modifie le booléen est détruit

    /**
     * @brief      Sets the dropped booleab
     *
     * @param[in]  dropped  Indicates if dropped or not
     */
    void setDropped(bool dropped);
    //modifie le booléen est drop

    /**
     * @brief      Sets the object position.
     *
     * @param[in]  pos   The new value
     */
    void setPos(const Rectangle & pos);
    //modifie la position de l'objet

    /**
     * @brief      Sets the object index
     *
     * @param[in]  index  The index
     */
    void setIndex(unsigned int index);
    //modifie l'indice de l'objet pour l'insérer dans un tableau d'objets
    //exemple : inventaire
    
    /**
     * @brief      Gets the object type.
     *
     * @return     The object type.
     */
    std::string getObjectType() const;
    //retourne le type de l'objet sous forme de string

    /**
     * @brief      Sets the object name
     *
     * @param[in]  name  The object name
     */
    void setNameObject(const std::string &name);
    //modifie le nom d'un objet

    /**
     * @brief      Assignment operator.
     *
     * @param[in]  copie  The object to be copied
     *
     * @return     The result of the assignment
     */
    Object& operator=(const Object &copie);
};



#endif
