#pragma once
#include <vector>

class Vertex
	/*
	This class represents a vertex. A vertex holds the edges it is connected to, represented by integers.
	*/
{
public:
	Vertex(std::vector<int> edges);
	std::vector<int> _edges;

};

