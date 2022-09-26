#pragma once
#include "Tile.h"

class World
{
	static const int size = 8;
	Tile* tiles;
public:
	World();
	void GetVertices(std::vector<Vertex>* vertexData, std::vector<unsigned int>* indexData);
};