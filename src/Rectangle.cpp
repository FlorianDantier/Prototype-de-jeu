#include "Rectangle.h"

Rectangle::Rectangle()
{}

Rectangle::Rectangle(const int x, const int y, const int w, const int h) : m_position(x, y), m_dimension(w, h)
{}

Rectangle::Rectangle(const Vec2<int> &position, const Vec2<int> &dimension) : m_position(position), m_dimension(dimension)
{}

bool Rectangle::in(const Vec2<int> & point)
{
    if(point.x > m_position.x && point.y > m_position.y
            && point.x < m_position.x + m_dimension.x
            && point.y < m_position.y + m_dimension.y)
        return true;
    else
        return false;
}

bool Rectangle::in(const Rectangle &rect)
{
    if((m_position.x >= rect.m_position.x + rect.m_dimension.x)      // trop à droite
        || (m_position.x + m_dimension.x <= rect.m_position.x)       // trop à gauche
        || (m_position.y >= rect.m_position.y + rect.m_dimension.y)  // trop en bas
        || (m_position.y + m_dimension.y <= rect.m_position.y))      // trop en haut
              return false;
       else
              return true;
}

Vec2<int> Rectangle::centre()
{
    return Vec2<int>(m_position.x + m_dimension.x/2, m_position.y + m_dimension.y/2);
}
