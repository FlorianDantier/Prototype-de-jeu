#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL2/SDL.h>
#include "Vec2.h"

class Rectangle
{
public:
    SDL_Rect rectangle;
    Rectangle();
    Rectangle(const int x, const int y, const int w, const int h);
    Rectangle(const Vec2<int> position, const Vec2<int> & dimension);
    bool in(const Vec2<int> &point);
    Vec2<int> centre();
};

#endif // RECTANGLE_H
