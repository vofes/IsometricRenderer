#pragma once
#include <vector>
#include "Vertex.h"

struct Mesh
{
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indicies;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies)
		: m_vertices(vertices), m_indicies(indicies)
	{

	}
};