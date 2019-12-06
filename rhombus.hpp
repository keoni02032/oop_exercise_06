#ifndef D_RHOMBUS_HPP_
#define D_RHOMBUS_HPP_ 1

#include <algorithm>
#include <iostream>
#include <assert.h>
#include <cmath>

#include "vertex.hpp"

template<class T>
struct rhombus {
public:
    rhombus (std::istream& is);

    bool correct() const;

    vertex<double> center() const;
    double area() const;
    double perimeter() const;
    void print() const;
private:
    vertex<T> a1, a2, a3, a4;
};


template <class T>
rhombus<T>::rhombus(std::istream& is) {
    is >> a1 >> a2 >> a3 >> a4;
    assert(correct());
}

template <class T>
bool rhombus<T>::correct() const {
    T str1, str2, str3, str4;
    str1 = sqrt((a2.x - a1.x) * (a2.x - a1.x) + (a2.y - a1.y) * (a2.y - a1.y));
    str2 = sqrt((a3.x - a2.x) * (a3.x - a2.x) + (a3.y - a2.y) * (a3.y - a2.y));
    str3 = sqrt((a4.x - a3.x) * (a4.x - a3.x) + (a4.y - a3.y) * (a4.y - a3.y));
    str4 = sqrt((a1.x - a4.x) * (a1.x - a4.x) + (a1.y - a4.y) * (a1.y - a4.y));
    if (str1 == str2 && str2 == str3 && str3 == str4) {
        return true;
    }
    return false;
}

template <class T>
vertex<double> rhombus<T>::center() const {
    vertex<double> p;
    p.x = (a1.x + a2.x + a3.x + a4.x) / 4;
    p.y = (a1.y + a2.y + a3.y + a4.y) / 4;
    return p;
}

template <class T>
double rhombus<T>::area() const {
    const T s1 = 0.5 * abs((a2.x - a1.x) * (a3.y - a1.y) - (a3.x - a1.x) * (a2.y - a1.y));
    const T s2 = 0.5 * abs((a3.x - a1.x) * (a4.y - a1.y) - (a4.x - a1.x) * (a3.y - a1.y));
    return s1 + s2;
}

template <class T>
double rhombus<T>::perimeter() const {
    const T str1 = sqrt((a2.x - a1.x) * (a2.x - a1.x) + (a2.y - a1.y) * (a2.y - a1.y));
    const T str2 = sqrt((a3.x - a2.x) * (a3.x - a2.x) + (a3.y - a2.y) * (a3.y - a2.y));
    const T str3 = sqrt((a4.x - a3.x) * (a4.x - a3.x) + (a4.y - a3.y) * (a4.y - a3.y));
    const T str4 = sqrt((a1.x - a4.x) * (a1.x - a4.x) + (a1.y - a4.y) * (a1.y - a4.y));
    return str1 + str2 + str3 + str4;
}

template <class T>
void rhombus<T>::print() const {
    std::cout << a1 << ' ' << a2 << ' ' << a3 << ' ' << a4 << '\n';
}

#endif