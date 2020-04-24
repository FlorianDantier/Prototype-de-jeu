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

void Rectangle::setCentre(const Vec2<int> &c)
{
    m_position.x += c.x;
    m_position.y += c.y;
}

void Rectangle::setPointMin(const Vec2<int> &ptMin)
{
    m_position = ptMin;
}

void Rectangle::setPointMax(const Vec2<int> &ptMax)
{
    m_dimension.x = ptMax.x - m_position.x;
    m_dimension.y = ptMax.y - m_position.y;
}

Vec2<int> Rectangle::getPointMin() const
{
    return m_position;
}

Vec2<int> Rectangle::getPointMax() const
{
    return m_dimension + m_position;
}

int Rectangle::getXmin() const
{
    return m_position.x;
}

int Rectangle::getYmin() const
{
    return m_position.y;
}

int Rectangle::getXmax() const
{
    return m_position.x + m_dimension.x;
}

int Rectangle::getYmax() const
{
    return m_position.y + m_dimension.y;
}

void Rectangle::setXmin(const int xMin)
{
    m_position.x = xMin;
}

void Rectangle::setYmin(const int yMin)
{
    m_position.y = yMin;
}

void Rectangle::setXmax(const int xMax)
{
    m_dimension.x = xMax - m_position.x;
}

void Rectangle::setYmax(const int yMax)
{
    m_dimension.y = yMax - m_position.y;
}

Rectangle Rectangle::getDroit() const
{
    Vec2<int> pt1(getXmax(), getYmin());
    Vec2<int> pt2(getXmax(), getYmax());
    Rectangle r;
    r.setPointMin(pt1);
    r.setPointMax(pt2);

    return  r;
}

Rectangle Rectangle::getGauche() const
{
    Vec2<int> pt1(getXmin(), getYmin());
    Vec2<int> pt2(getXmin(), getYmax());
    Rectangle r;
    r.setPointMin(pt1);
    r.setPointMax(pt2);

    return  r;
}

Rectangle Rectangle::getHaut() const
{
    Vec2<int> pt1(getXmin(), getYmin());
    Vec2<int> pt2(getXmax(), getYmin());
    Rectangle r;
    r.setPointMin(pt1);
    r.setPointMax(pt2);

    return  r;
}

Rectangle Rectangle::getBas() const
{
    Vec2<int> pt1(getXmin(), getYmax());
    Vec2<int> pt2(getXmax(), getYmax());
    Rectangle r;
    r.setPointMin(pt1);
    r.setPointMax(pt2);

    return  r;
}




