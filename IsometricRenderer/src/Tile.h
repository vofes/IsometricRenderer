#pragma once
#include "Sprite.h"

class Tile
{
public:
	int id;
	Vector3 gridPos;
	Sprite sprite;

	Tile()
		:id(0), gridPos(Vector3())
	{

	}

	Tile(const int& id, const Vector3& pos)
		: id(id), gridPos(pos)
	{
		sprite = Sprite(pos, Vector2(1.0f, 1.0f), 0);
	}
};