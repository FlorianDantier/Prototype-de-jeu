#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Vec2.h"
#include <iostream>


struct DoubleRect;

/**
 * @brief      This class describes a rectangle.
 * 
 * A rectangle has a 2D position and dimension (width by height)
 * 
 * Example of usage:
 * @code
 * Rectangle car(200, 0, 60, 30);
 * 
 * Rectangle bus(70, 0, 120, 40);
 * 
 * //test the collision between the bus and the car
 * if (car.in(bus))
 * {
 *     std::cout << "Collision between the bus and the car" << std::endl;
 * }
 * @endcode
 */
class Rectangle
{
public:
    /**
     * The position of the rectangle (x, y)
     */
    Vec2<int> m_position;

    /**
     * The width and the height of the rectangle
     */
    Vec2<int> m_dimension;

    /**
     * @brief      Constructs a new instance of Rectangle
     */
    Rectangle();

    /**
     * @brief      Constructs a new instance of Rectangle
     *
     * @param[in]  x     x-axis position
     * @param[in]  y     y-axis position
     * @param[in]  w     rectangle width
     * @param[in]  h     rectangle height
     */
    Rectangle(const int x, const int y, const int w, const int h);

    /**
     * @brief      Constructs a new instance of Rectangle
     *
     * @param[in]  position   The rectangle position
     * @param[in]  dimension  The rectangle dimension
     */
    Rectangle(const Vec2<int> &position, const Vec2<int> & dimension);

    /**
     * @brief      Tests the collision between a point and this rectangle
     *
     * @param[in]  point  The coordinates of the point
     *
     * @return     True if there is a collision, otherwise it will returns false
     */
    bool in(const Vec2<int> &point);

    /**
     * @brief      Tests the collision between a rectangle and this rectangle
     *
     * @param[in]  rect  a constant reference to the second rectangle
     *
     * @return     True if there is a collision, otherwise it will returns false
     */
    bool in(const Rectangle & rect);

    /**
     * @brief      Get the center position of this rectangle
     *
     * @return     the position
     */
    Vec2<int> centre();

    /**
     * @brief      Sets the rectangle center
     *
     * @param[in]  c     The new position of the rectangle center
     */
    void setCentre(const Vec2<int> &c);

    /**
     * @brief      Sets the position of the bottom left vertex
     *
     * @param[in]  ptMin  The position of the bottom left vertex
     */
    void setPointMin(const Vec2<int> & ptMin);

    /**
     * @brief      Sets the positon the top right vertex
     *
     * @param[in]  ptMax  The position of the top right vertex
     */
    void setPointMax(const Vec2<int> & ptMax);

    /**
     * @brief      Gets the position of the bottom left vertex
     *
     * @return     The position of the bottom left vertex
     */
    Vec2<int> getPointMin() const;

    /**
     * @brief      Gets the position of the top right vertex
     *
     * @return     The position of the top right vertex
     */
    Vec2<int> getPointMax() const;

    /**
     * @brief      Gets the xmin.
     *
     * @return     The x-axis value of the vertices on the left
     */
    int getXmin() const;

    /**
     * @brief      Gets the ymin.
     *
     * @return     The y-axis value of the vertices on the bottom
     */
    int getYmin() const;

    /**
     * @brief      Gets the xmax.
     *
     * @return     The x-axis value of the vertices on the right
     */
    int getXmax() const;

    /**
     * @brief      Gets the ymax.
     *
     * @return     The y-axis value of the vertices on the top
     */
    int getYmax() const;

    /**
     * @brief      Sets the xmin.
     *
     * @param[in]  xMin  The new x-axis value of the vertices on the left
     */
    void setXmin(const int xMin);

    /**
     * @brief      Sets the ymin.
     *
     * @param[in]  yMin  The new y-axis value of the vertices on the bottom
     */
    void setYmin(const int yMin);

    /**
     * @brief      Sets the xmax.
     *
     * @param[in]  xMax  The new x-axis value of the vertices on the right
     */
    void setXmax(const int xMax);

    /**
     * @brief      Sets the ymax.
     *
     * @param[in]  yMax  The new y-axis value of the vertices on the top
     */
    void setYmax(const int yMax);

    /**
     * @brief      Gets the right border of this rectangle
     *
     * @return     A rectangle
     */
    Rectangle getDroit() const;

    /**
     * @brief      Gets the left border of this rectangle
     *
     * @return     A rectangle
     */
    Rectangle getGauche() const;

    /**
     * @brief      Gets the top border of this rectangle
     *
     * @return     A rectangle
     */
    Rectangle getHaut() const;

    /**
     * @brief      Gets the bottom border of the rectangle
     *
     * @return     A rectangle
     */
    Rectangle getBas() const;

    /**
     * @brief      Cut this rectangle in two rectangles whith a dimension divided by 2
     * 
     * The first rectangle is located near from the top left of this rectangle.
     * The second rectangle is located near from the bottom right of this rectangle.
     *
     * @return     A double rectangle
     */
    DoubleRect cut() const;
};


/**
 * @brief      Basic structure composed of two rectangles
 */
struct DoubleRect
{
    /**
     * first rectangle
     */
    Rectangle r1;
    /**
     * second rectangle
     */
    Rectangle r2;
};

#endif // RECTANGLE_H
