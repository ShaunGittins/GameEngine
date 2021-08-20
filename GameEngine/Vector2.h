#pragma once
#include <SDL_stdinc.h>

struct Vector2
{
public:
    Vector2();
    Vector2(float x, float y);

	float _x;
	float _y;

	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator*(const Uint32& rhs);
};