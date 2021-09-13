#pragma once
#include "Vector2.h"

static class Math
{
    Vector2 velocityTo(float x1, float x2, float y1, float y2) {
        float xDifference = x2 - x1;
        float yDifference = y2 - y1;

        float resultX = xDifference / SDL_sqrt(xDifference * xDifference + yDifference * yDifference);
        float resultY = yDifference / SDL_sqrt(xDifference * xDifference + yDifference * yDifference);

        return Vector2(resultX, resultY);
    }

    double angleTo(Vector2 from, Vector2 to) {
        Vector2 myVector = to - from;
        double angle = SDL_atan2(myVector._y, myVector._x);
        return angle;
    }
};

