#pragma once
#include "Vector.h"
#include "Mesh.h"

class Sprite
{
public:
	Vector3 position;
	Vector2 scale;
	unsigned int texture;
	Mesh GetMeshData() const;
	Sprite(const Vector3& position, const Vector2& scale, const unsigned int& texture);
	Sprite();
private:

};