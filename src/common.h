#ifndef COMMON_H
#define COMMON_H

#include "Vec2.h"
enum GameStatus
{
    run = 0,
    standBy,
    home,
    noValue
};



const Vec2<unsigned int> windowSize(800, 800);

const int impact = 3;

const Vec2<int> top(0, -5);
const Vec2<int> bottom(0, 5);
const Vec2<int> left(-5, 0);
const Vec2<int> right(5, 0);



#endif // COMMON_H
