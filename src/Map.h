#ifndef MAP_H
#define MAP_H

#include "Rectangle.h"

class Map
{
private:
    Rectangle* m_decorTab;
    unsigned int m_nbDecor;
public:
    Map();
    Map(const unsigned int nbDecor);
    ~Map();

    void setDecor(const unsigned int indice, const Rectangle &r);
    Rectangle &getDecor(const unsigned int indice) const;

};

#endif // MAP_H
