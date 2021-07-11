#pragma once

#include <vector>

#include "Matrix.h"
#include "Matrix.cpp"
#include "Vertex.h"

class WalkCounter
{
public:
	WalkCounter() = default;

	void promptVertexCount();
	void promptVertices();
	void printVertices();

	void makeAdjMat();

	void printAjdMat();

	void promptWalks();

private:
	Matrix<double> _adjMat{ 1,1 };
	int _vertexCount = 0;
	std::vector<Vertex> _vertices;

};

