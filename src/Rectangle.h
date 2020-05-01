#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Vec2.h"
#include <iostream>


struct DoubleRect;
struct FourRect;
struct HeightRect;

class Rectangle
{
public:
    Vec2<int> m_position;
    Vec2<int> m_dimension;
    Rectangle();
    Rectangle(const int x, const int y, const int w, const int h);
    Rectangle(const Vec2<int> &position, const Vec2<int> & dimension);
    bool in(const Vec2<int> &point) const;
    bool in(const Rectangle & rect) const;
    Vec2<int> centre();
    void setCentre(const Vec2<int> &c);

    void setPointMin(const Vec2<int> & ptMin);
    void setPointMax(const Vec2<int> & ptMax);

    Vec2<int> getPointMin() const;
    Vec2<int> getPointMax() const;

    int getXmin() const;
    int getYmin() const;
    int getXmax() const;
    int getYmax() const;

    void setXmin(const int xMin);
    void setYmin(const int yMin);
    void setXmax(const int xMax);
    void setYmax(const int yMax);

    Rectangle getDroit() const;
    Rectangle getGauche() const;
    Rectangle getHaut() const;
    Rectangle getBas() const;
    DoubleRect cutTwo() const;
    FourRect cutFour() const;
    Rectangle* cutHeight() const;

    DoubleRect cutTwoBis() const;
    FourRect cutFourBis() const;
    Rectangle* cutHeightBis() const;
};

struct DoubleRect
{
    Rectangle r1;
    Rectangle r2;
};

struct FourRect
{
    Rectangle r1;
    Rectangle r2;
    Rectangle r3;
    Rectangle r4;
};

struct HeightRect
{
    FourRect fr1;
    FourRect fr2;
};

#endif // RECTANGLE_H
