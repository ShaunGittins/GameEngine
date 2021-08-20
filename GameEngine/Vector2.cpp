#include "Vector2.h"

Vector2::Vector2()
{
    _x = 0.0f;
    _y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
    _x = x;
    _y = y;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
    this->_x += rhs._x;
    this->_y += rhs._y;
    return *this;
}
