#pragma once

#include <vector>

#include "Matrix.h"
#include "Matrix.cpp"
#include "Vertex.h"

class WalkCounter
	/*
	The "backend" class for the "game". This class wraps all of the 
	functionality of the matrices and vertices.
	*/
{
public:
	WalkCounter() = default;

	void playGame();

	void promptVertexCount();
	void promptVertices();
	void printVertices();

	void makeAdjMat();

	void printWalkMat(int walks);
	void printAdjMat();

	void promptWalks();
	void promptStats();
	void promptInfo();

	void endedGame();

private:
	Matrix<double> _adjMat{ 1,1 };
	Matrix<double> _walkMat{ 1,1 };
	int _vertexCount = 0;
	std::vector<Vertex> _vertices;

};

