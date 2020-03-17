#ifndef VEC2_H
#define VEC2_H

template <typename T>
class Vec2
{
public:
    T x;
    T y;
    Vec2();
    Vec2(T x, T y);
    // Spécialisation pour le type int avec un SDL_Point ?
};

template <typename T>
Vec2<T>::Vec2()
{
    x = 0;
    y = 0;
}


template <typename T>
Vec2<T>::Vec2(T f_x, T f_y)
{
    x = f_x;
    y = f_y;
}

#endif // VEC2_H
