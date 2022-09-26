#pragma once
#include "Vector.h"

class IsometricMath
{
public:
	static Vector2 ConvertGridToIsometric(const Vector2& grid);
	static Vector2 ConvertIsometricToGrid(const Vector2& iso);
};