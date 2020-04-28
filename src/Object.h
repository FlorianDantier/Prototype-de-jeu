#ifndef OBJECT_H
#define OBJECT_H

#include "Image.h"
#include <string>

enum ObjectType {weapon,armor,other};
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
    Object();
    //constructeur par défaut
    Object(const std::string & name,ObjectType type,unsigned int index,
           const Rectangle & pos,int value,bool looted,bool dropped);
    //constructeur prenant en paramètre le nom, le type, l'indice,
    //la position et le bonus de l'objet
    //Object(const Object &copie);
    //contructeur par copie
    ~Object();
    //destructeur
    std::string getNameObject() const;
    //retourne le nom de l'objet
    ObjectType getType() const;
    //retourne le type d'objet
    unsigned int getIndex() const;
    //retourne l'indice de l'objet
    Rectangle& getPos() const;
    //retourne la position sous forme de rectangle
    bool isLooted() const;
    // retourne vrai si l'objet est loot
    int getValue() const;
    //retourne la valeur du bonus de l'objet
    bool isDestroyed() const;
    //retourne vrai si l'objet est détruit/à détruire
    bool isDropped() const;
    //retourne vrai si l'objet a été laissé tombé (par un monstre)
    void setLooted(bool looted);
    //modifie le booléen est loot
    void setDestroyed(bool destroyed);
    //modifie le booléen est détruit
    void setDropped(bool dropped);
    //modifie le booléen est drop
    void setPos(const Rectangle & pos);
    //modifie la position de l'objet
    void setIndex(unsigned int index);
    //modifie l'indice de l'objet pour l'insérer dans un tableau d'objets
    //exemple : inventaire
    std::string getObjectType() const;
    //retourne le type de l'objet sous forme de string
    void setNameObject(const std::string &name);
    //modifie le nom d'un objet
    Object& operator=(const Object &copie);
};



#endif
