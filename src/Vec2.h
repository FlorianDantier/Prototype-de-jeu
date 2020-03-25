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
    Vec2<T> &operator+=(const Vec2<T> & add);
    Vec2<T> &operator-=(const Vec2<T> & add);
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

template<typename T>
Vec2<T> &Vec2<T>::operator+=(const Vec2<T> &add)
{
    x += add.x;
    y += add.y;

    return *this;
}

template<typename T>
Vec2<T> &Vec2<T>::operator-=(const Vec2<T> &add)
{
    x -= add.x;
    y -= add.y;

    return *this;
}



#endif // VEC2_H
