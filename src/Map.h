#ifndef MAP_H
#define MAP_H

#include "Rectangle.h"

enum Decal
{
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

     Rectangle *m_tabOutZones;
     unsigned int m_nbOutZone;

    void initMap1();
    void initMap2();
    void initInstance1();

public:
    Map();
    Map(const unsigned int nbDecor, unsigned int nbOutZone, unsigned int map);
    ~Map();
    void setDecor(const unsigned int indice, const Rectangle &r);
    void setDecorDiago(const unsigned int start, const Rectangle &diago, const Decal & d);
    Rectangle &getDecor(const unsigned int indice) const;
    Rectangle *getAllDecor() const;

    void setOutZone(const unsigned int indice, const Rectangle & r);
    Rectangle& getOutZone(unsigned int indice) const;


    bool isInOutZone(const Rectangle & r, unsigned int indice);
    unsigned int getNbDecor() const;

};

#endif // MAP_H
