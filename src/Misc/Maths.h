#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <Windows.h>
#include <cmath>

using namespace std;

constexpr float PI = 3.14159265;

template <typename T>
T toRadians(T degrees)
{
    return degrees * PI / 180;
}

template <typename T>
T toDegrees(T radians)
{
    return (radians * 180) / PI;
}

inline float Dist(const sf::Vector2f &v, const sf::Vector2f &u)
{
	return sqrt(pow(v.x-u.x, 2) + pow(v.y-u.y, 2));
}

inline float Norm(const sf::Vector2f &v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

inline float Clamp(const float f,const float min,const float max)
{
	if (f > max)
		return max;
	else if (f < min)
		return min;
	else
		return f;
}

inline double fastPow(const double a, const double b) {
    union {
        double d;
        int x[2];
    } u = { a };
    u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
    u.x[0] = 0;
    return u.d;
}