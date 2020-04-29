#ifndef MAP_H
#define MAP_H

#include "Rectangle.h"

enum Decal{
    TopRight = 0,
    TopLeft,
    BottomRight,
    BottomLeft
};


class Map
{
private:
    Rectangle* m_decorTab;
    unsigned int m_nbDecor;

    void initMap1();
    void initMap2();
public:
    Map();
    Map(const unsigned int nbDecor, unsigned int map);
    ~Map();
    void setDecor(const unsigned int indice, const Rectangle &r);
    void setDecorDiago(const unsigned int start, const Rectangle &diago, const Decal & d);
    Rectangle &getDecor(const unsigned int indice) const;

    unsigned int getNbDecor() const;

};

#endif // MAP_H
