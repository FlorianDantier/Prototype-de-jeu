#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Vec2.h"
#include <iostream>

class Rectangle
{
public:
    Vec2<int> m_position;
    Vec2<int> m_dimension;
    Rectangle();
    Rectangle(const int x, const int y, const int w, const int h);
    Rectangle(const Vec2<int> &position, const Vec2<int> & dimension);
    bool in(const Vec2<int> &point);
    bool in(const Rectangle & rect);
    Vec2<int> centre();
};

#endif // RECTANGLE_H
