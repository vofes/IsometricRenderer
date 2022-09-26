#pragma once
#include "Vector.h"

struct Vertex
{
	Vector3 pos;
	Vector2 uv;
	Vector4 color;
	float textureID;

	Vertex()
		: pos(Vector3()),
		uv(Vector2()),
		color({ 1.0f, 1.0f, 1.0f, 1.0f }),
		textureID(-1.0f)
	{

	}
};