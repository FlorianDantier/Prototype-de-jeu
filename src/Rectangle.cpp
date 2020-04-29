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

DoubleRect Rectangle::cutTwo() const
{
    DoubleRect dr;
    dr.r1 = Rectangle(m_position.x, m_position.y + m_dimension.y / 2, m_dimension.x / 2, m_dimension.y / 2);
    dr.r2 = Rectangle(m_position.x + m_dimension.x / 2, m_position.y, m_dimension.x / 2, m_dimension.y / 2);

    return dr;
}

FourRect Rectangle::cutFour() const
{
    FourRect fr;
    DoubleRect two = cutTwo();
    fr.r1 = two.r1.cutTwo().r1;
    fr.r2 = two.r1.cutTwo().r2;
    fr.r3 = two.r2.cutTwo().r1;
    fr.r4 = two.r2.cutTwo().r2;

    return fr;
}

Rectangle* Rectangle::cutHeight() const
{
    Rectangle* tab = new Rectangle[8];
    FourRect four = cutFour();

    tab[0] = four.r1.cutTwo().r1;


    tab[1] = four.r1.cutTwo().r2;


    tab[2] = four.r2.cutTwo().r1;


    tab[3] = four.r2.cutTwo().r2;


    tab[4] = four.r3.cutTwo().r1;


    tab[5] = four.r3.cutTwo().r2;


    tab[6] = four.r4.cutTwo().r1;


    tab[7] = four.r4.cutTwo().r2;


    return tab;
}

DoubleRect Rectangle::cutTwoBis() const
{
    DoubleRect dr;
    dr.r1 = Rectangle(m_position.x, m_position.y, m_dimension.x / 2, m_dimension.y / 2);
    dr.r2 = Rectangle(m_position.x + m_dimension.x / 2, m_position.y + m_dimension.y / 2,
                      m_dimension.x / 2, m_dimension.y / 2);

    return  dr;
}

FourRect Rectangle::cutFourBis() const
{
    FourRect fr;
    DoubleRect dr = cutTwoBis();
    fr.r1 = dr.r1.cutTwoBis().r1;
    fr.r2 = dr.r1.cutTwoBis().r2;
    fr.r3 = dr.r2.cutTwoBis().r1;
    fr.r4 = dr.r2.cutTwoBis().r2;

    return fr;
}

Rectangle *Rectangle::cutHeightBis() const
{
    Rectangle *tab = new Rectangle[8];
    FourRect fr = cutFourBis();
    tab[0] = fr.r1.cutTwoBis().r1;
    tab[1] = fr.r1.cutTwoBis().r2;
    tab[2] = fr.r2.cutTwoBis().r1;
    tab[3] = fr.r2.cutTwoBis().r2;
    tab[4] = fr.r3.cutTwoBis().r1;
    tab[5] = fr.r3.cutTwoBis().r2;
    tab[6] = fr.r4.cutTwoBis().r1;
    tab[7] = fr.r4.cutTwoBis().r2;

    return  tab;
}




