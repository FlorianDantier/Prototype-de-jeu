#include "Rectangle.h"

Rectangle::Rectangle()
{
    rectangle = {0, 0, 0, 0};
}

Rectangle::Rectangle(const int x, const int y, const int w, const int h)
{
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
}

Rectangle::Rectangle(const Vec2<int> position, const Vec2<int> &dimension)
{
    rectangle.x = position.x;
    rectangle.y = position.y;
    rectangle.w = dimension.x;
    rectangle.h = dimension.y;
}

bool Rectangle::in(const Vec2<int> & point)
{
    if(point.x > rectangle.x && point.y > rectangle.y
            && point.x < rectangle.x + rectangle.w
            && point.y < rectangle.y + rectangle.h)
        return true;
    else
        return false;
}

Vec2<int> Rectangle::centre()
{
    return Vec2(rectangle.x + rectangle.w/2, rectangle.y + rectangle.h/2);
}
