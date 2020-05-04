#ifndef VEC2_H
#define VEC2_H

#include <math.h>

template <typename T>
/**
 * @brief      This class describes a two dimensions vector.
 */
class Vec2
{
public:
    T x;
    T y;
    /**
     * @brief      Constructs a new instance.
     */
    Vec2();
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  x     the vector x-coordinate
     * @param[in]  y     the vector y-coordinate
     */
    Vec2(T x, T y);

    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  v     the 2D vector to be copied
     */
    Vec2(const Vec2<T> & v);

    /**
     * @brief      Gives the distance between the (x, y) point and the the point (v.x, v.y)
     *
     * @param[in]  v     the second point
     *
     * @return     a decimal value of the distance
     */
    float distance(const Vec2<T> & v);

    /**
     * @brief      Addition assignment operator.
     *
     * @param[in]  add   The second vector
     *
     * @return     The result of the addition assignment
     */
    Vec2<T> &operator+=(const Vec2<T> & add);

    /**
     * @brief      Subtraction assignment operator.
     *
     * @param[in]  add   The second vector
     *
     * @return     The result of the subtraction assignment
     */
    Vec2<T> &operator-=(const Vec2<T> & add);

    /**
     * @brief      Multiplication assignment operator.
     *
     * @param[in]  scalar  The scalar
     *
     * @return     The result of the multiplication assignment
     */
    Vec2<T> &operator*=(const T scalar);

    /**
     * @brief      Division assignment operator.
     *
     * @param[in]  scalar  The scalar
     *
     * @return     The result of the division assignment
     */
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

template<typename T>
bool operator==(const Vec2<T> & v1, const Vec2<T> & v2)
{
    if(v1.x == v2.x && v1.y == v2.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}



#endif // VEC2_H
