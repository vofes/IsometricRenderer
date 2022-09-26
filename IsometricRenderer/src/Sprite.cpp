#include "Sprite.h"

Mesh Sprite::GetMeshData() const
{
	Vertex v0;
	v0.pos = Vector3(-0.5f, -0.5f, 0.0f) + position;
	v0.uv = { 0.0f, 0.0f };
	v0.textureID = (float)texture;
	Vertex v1;
	v1.pos = Vector3(0.5f, -0.5f, 0.0f) + position;
	v1.uv = { 1.0f, 0.0f };
	v1.textureID = (float)texture;
	Vertex v2;
	v2.pos = Vector3(0.5f, 0.5f, 0.0f) + position;
	v2.uv = { 1.0f, 1.0f };
	v2.textureID = (float)texture;
	Vertex v3;
	v3.pos = Vector3(-0.5f, 0.5f, 0.0f) + position;
	v3.uv = { 0.0f, 1.0f };
	v3.textureID = (float)texture;

	return Mesh(
		{ v0, v1, v2, v3 }, 
		{ 0, 1, 2, 2, 3, 0 }
	);
}

Sprite::Sprite(const Vector3& position, const Vector2& scale, const unsigned int& texture)
	: position(position), scale(scale), texture(texture)
{

}

Sprite::Sprite()
	: position(Vector3()), scale(Vector2()), texture(0)
{
}
