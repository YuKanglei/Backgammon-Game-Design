#pragma once

namespace utils {

template<typename T>
class point final
{
    public:
    point() = default;
    point(T x, T y) : m_x(x), m_y(y) {}

    T get_x() const { return m_x; }
    T get_y() const { return m_y; }

    /**
     * 声明并实现+=、-=、*=、/=运算符重载
     * e.g.
     * inline point<T> & operator+=(const point<T> & p);
    */
    inline point<T>& operator+=(const point<T>& p) {
        m_x += p.m_x;
        m_y += p.m_y;
        return *this;
    }

    inline point<T>& operator-=(const point<T>& p) {
        m_x -= p.m_x;
        m_y -= p.m_y;
        return *this;
    }

    inline point<T>& operator*=(T value) {
        m_x *= value;
        m_y *= value;
        return *this;
    }

    inline point<T>& operator/=(T value) {
        m_x /= value;
        m_y /= value;
        return *this;
    }

    /**
    * 声明并实现==、!=、+、-、*、/、+、-运算符重载
    * e.g.
    * template<class Y>
    * friend inline bool operator==(const point<T> & p1, const point<T> & p2);
    */
    // 比较运算符重载
    template<typename Y>
    friend inline bool operator==(const point<Y>& p1, const point<Y>& p2);

    template<typename Y>
    friend inline bool operator!=(const point<Y>& p1, const point<Y>& p2);

    // 算术运算符重载
    template<typename Y>
    friend inline point<Y> operator+(const point<Y>& p1, const point<Y>& p2);

    template<typename Y>
    friend inline point<Y> operator-(const point<Y>& p1, const point<Y>& p2);

    template<typename Y>
    friend inline point<Y> operator*(const point<Y>& p, Y value);

    template<typename Y>
    friend inline point<Y> operator*(Y value, const point<Y>& p);

    template<typename Y>
    friend inline point<Y> operator/(const point<Y>& p, Y value);

    private:
    T m_x{0};
    T m_y{0};
};

// 比较运算符重载的实现
template<typename Y>
inline bool operator==(const point<Y>& p1, const point<Y>& p2) {
    return p1.m_x == p2.m_x && p1.m_y == p2.m_y;
}

template<typename Y>
inline bool operator!=(const point<Y>& p1, const point<Y>& p2) {
    return !(p1 == p2);
}

// 算术运算符重载的实现
template<typename Y>
inline point<Y> operator+(const point<Y>& p1, const point<Y>& p2) {
    return point<Y>(p1.m_x + p2.m_x, p1.m_y + p2.m_y);
}

template<typename Y>
inline point<Y> operator-(const point<Y>& p1, const point<Y>& p2) {
    return point<Y>(p1.m_x - p2.m_x, p1.m_y - p2.m_y);
}

template<typename Y>
inline point<Y> operator*(const point<Y>& p, Y value) {
    return point<Y>(p.m_x * value, p.m_y * value);
}

template<typename Y>
inline point<Y> operator*(Y value, const point<Y>& p) {
    return point<Y>(p.m_x * value, p.m_y * value);
}

template<typename Y>
inline point<Y> operator/(const point<Y>& p, Y value) {
    return point<Y>(p.m_x / value, p.m_y / value);
}

// -------------------------------------------------------------

using point_uint = point<unsigned int>;
using point_int = point<int>;
using point_float = point<float>;
using point_double = point<double>;

} // namespace utils