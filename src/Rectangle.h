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

    void debug()
    {
        std::cout<<"pos x : ";
        std::cout<<m_position.x<<std::endl;

        std::cout<<"pos y : ";
        std::cout<<m_position.x<<std::endl;

        std::cout<<"dim x : ";
        std::cout<<m_dimension.x<<std::endl;

        std::cout<<"dim y : ";
        std::cout<<m_dimension.y<<std::endl;
    }
};

#endif // RECTANGLE_H
