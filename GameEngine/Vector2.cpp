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



bool Vector2::operator==(const Vector2& rhs)
{
    return this->_x == rhs._x && this->_y == rhs._y;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
    this->_x += rhs._x;
    this->_y += rhs._y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
    this->_x -= rhs._x;
    this->_y -= rhs._y;
    return *this;
}

Vector2& Vector2::operator-(const Vector2& rhs)
{
    Vector2 result;
    result._x = this->_x - rhs._x;
    result._x = this->_y - rhs._y;
    return result;
}

Vector2& Vector2::operator+(const Vector2& rhs)
{
    Vector2 result;
    result._x = this->_x + rhs._x;
    result._x = this->_y + rhs._y;
    return result;
}

Vector2& Vector2::operator*(const Uint32& rhs)
{
    this->_x *= rhs;
    this->_y *= rhs;
    return *this;
}
