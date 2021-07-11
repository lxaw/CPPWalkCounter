#include <string>
#include <iostream>
#include <vector>

#include "WalkCounter.h"
#include "Vertex.h"


void WalkCounter::promptVertexCount() {
	std::cout << "How many vertices in your graph?\n";
	std::cin >> _vertexCount;
}

void WalkCounter::promptVertices() {
	std::cout << "The graph has " << _vertexCount << " vertices.\n";
	for (int i = 1;i < _vertexCount+1;++i) {
		std::vector<int> adjacentVertices;
		std::cout << "Entering data for vertex " << i << "\n";
		std::cout << "Enter the vertices that are connected to vertex " << i <<"\nEnter \"q\" to stop.\n";
		int counter = 1;
		bool running = true;
		while (counter < _vertexCount && running) {
			std::string ui;
			std::cin >> ui;
			if (ui == "q") {
				running = false;
				break;
			}
			
			int vert = std::stod(ui);
			adjacentVertices.push_back(vert);
			counter++;
		}
		Vertex v{ adjacentVertices };
		_vertices.push_back(v);
	}
}

void WalkCounter::makeAdjMat() {
	Matrix<double> adjMat{ _vertexCount,_vertexCount };

	for (int i = 0;i < _vertexCount;i++) {
		std::vector<int> vEdges = _vertices[i]._edges;
		for (int j = 0;j < vEdges.size();j++) {
			adjMat.setAtRowCol(1,i,vEdges[j]-1);
		}
	}
	_adjMat = adjMat;
}

void WalkCounter::promptWalks() {
	std::cout << "Enter the walk length you would like a count of: ";
	int walkLength;
	std::cin >> walkLength;
	std::cout << "Now finding walks of length: " << walkLength << "\n.";
	Matrix<double> mat = _adjMat;
	for (int i = 0;i < walkLength - 1;++i) {
		Matrix<double> temp = mat * _adjMat;
		mat = temp;
	}
	mat.print();
}

void WalkCounter::printAjdMat() {
	std::cout << "The Adjacency Matrix looks like:\n";
	_adjMat.print();
}

void WalkCounter::printVertices() {
	std::cout << "Here are all the vertices and their connections:\n";
	for (int i = 0;i < _vertices.size();++i) {
		std::cout << "Vertex " << i + 1<< "\n";
		std::cout << "Connections: " << "\n";
		for (int j = 0;j < _vertices[i]._edges.size();j++) {
			std::cout << _vertices[i]._edges[j] << " ";
		}
		std::cout << "\n";
	}
}








