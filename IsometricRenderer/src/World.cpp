#include "World.h"
#include "IsometricMath.h"
World::World()
{
	tiles = new Tile[size * size]; // AAAA NEW
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			Vector3 pos = Vector3(IsometricMath::ConvertGridToIsometric(Vector2(x, y)));
			pos.z = (x + y) / -16.0f;
			pos.y -= 2;
			tiles[x * size + y] = Tile(1, pos);
		}
	}
}

void World::GetVertices(std::vector<Vertex>* vertexData, std::vector<unsigned int>* indexData)
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (tiles[x * size + y].id == 0)
				continue;
			Mesh mesh = tiles[x * size + y].sprite.GetMeshData();
			for (int a = 0; a < mesh.m_indicies.size(); a++)
				(*indexData).push_back(mesh.m_indicies[a] + (*vertexData).size());
			(*vertexData).insert((*vertexData).end(), mesh.m_vertices.begin(), mesh.m_vertices.end());
		}
	}
}
