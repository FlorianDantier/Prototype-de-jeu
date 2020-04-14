#ifndef VEC2_H
#define VEC2_H

#include <math.h>

template <typename T>
class Vec2
{
public:
    T x;
    T y;
    Vec2();
    Vec2(T x, T y);
    Vec2(const Vec2<T> & v);
    float distance(const Vec2<T> & v);
    Vec2<T> &operator+=(const Vec2<T> & add);
    Vec2<T> &operator-=(const Vec2<T> & add);
    Vec2<T> &operator*=(const T scalar);
    Vec2<T> &operator/=(const T scalar);
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
Vec2<T>::Vec2(const Vec2<T> &v)
{
    x = v.x;
    y = v.y;
}

template<typename T>
float Vec2<T>::distance(const Vec2<T> &v)
{
    return  sqrt((x - v.x)*(x - v.x) + (y - v.y) * (y - v.y));
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

template <typename T>
Vec2<T> &Vec2<T>::operator*=(const T scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

template<typename T>
Vec2<T> &Vec2<T>::operator/=(const T scalar)
{
    x /= scalar;
    y /= scalar;

    return *this;
}

template<typename T>
Vec2<T> operator+(const Vec2<T> & v1, const Vec2<T> & v2)
{
    Vec2<T> r(v1);
    r+=v2;

    return r;
}

template<typename T>
Vec2<T> operator-(const Vec2<T> & v1, const Vec2<T> & v2)
{
    Vec2<T> r(v1);
    r-=v2;

    return r;
}

template<typename T>
Vec2<T> operator*(const Vec2<T> & v1, const T scalar)
{
    Vec2<T> r(v1);
    r*=scalar;

    return r;
}

template<typename T>
Vec2<T> operator*(const T scalar, const Vec2<T> & v1)
{
    Vec2<T> r(v1);
    r*=scalar;

    return r;
}


template<typename T>
Vec2<T> operator/(const Vec2<T> & v1, const T scalar)
{
    Vec2<T> r(v1);
    r/=scalar;

    return r;
}

template<typename T>
Vec2<T> operator/(const T scalar, const Vec2<T> & v1)
{
    Vec2<T> r(v1);
    r/=scalar;

    return r;
}

#endif // VEC2_H
