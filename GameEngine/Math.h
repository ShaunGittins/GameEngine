#pragma once
#include "Vector2.h"
#include <math.h>

namespace Math
{
    Vector2 velocityTo(Vector2 from, Vector2 to) {
        float xDifference = to._x - from._x;
        float yDifference = to._y - from._y;

        float resultX = xDifference / sqrt(xDifference * xDifference + yDifference * yDifference);
        float resultY = yDifference / sqrt(xDifference * xDifference + yDifference * yDifference);

        return Vector2(resultX, resultY);
    }

    double angleTo(Vector2 from, Vector2 to) {
        double deltaY = (static_cast<double>(from._y) - static_cast<double>(to._y));
        double deltaX = (static_cast<double>(to._x) - static_cast<double>(from._x));
        double result = atan2(deltaY, deltaX) * 180 / M_PI;
        return (result < 0) ? (360 + result) : result;
    }
};

