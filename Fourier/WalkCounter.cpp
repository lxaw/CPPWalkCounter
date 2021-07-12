#include <string>
#include <iostream>
#include <vector>

#include "WalkCounter.h"
#include "Vertex.h"

void WalkCounter::playGame() {
	promptVertexCount();
	promptVertices();
	printVertices();
	makeAdjMat();
	printAdjMat();
	promptStats();
	promptWalks();
	promptStats();
	
	bool running = true;
	while (running) {
		std::cout << "Want more walks? \"y\" / \"n\"\n";
		std::string ui;
		std::cin >> ui;
		if (ui == "n") {
			endedGame();
			running = false;
			break;
		}
		else {
			promptWalks();
			promptStats();
		}
	}
}
void WalkCounter::endedGame() {
	std::cout << "Goodbye!\n";
}

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
			
			int vert = std::atoi(ui.c_str());
			if (vert > 0 && vert <= _vertexCount)
			{
				adjacentVertices.push_back(vert);
				counter++;
			}
			else {
				std::cout << "Try again.\n";
			}
		}
		Vertex v{ adjacentVertices };
		_vertices.push_back(v);
	}
}

void WalkCounter::makeAdjMat() {
	Matrix<double> adjMat{ _vertexCount,_vertexCount };

	for (int i = 0;i < _vertexCount;i++) {
		std::vector<int> vEdges = _vertices[i]._edges;
		for (size_t j = 0;j < vEdges.size();j++) {
			adjMat.setAtRowCol(1,i,vEdges[j]-1);
		}
	}
	_adjMat = adjMat;
	_walkMat = adjMat;
}

void WalkCounter::promptWalks() {
	std::cout << "Enter the walk length you would like a count of: ";
	int walkLength;
	std::cin >> walkLength;
	std::cout << "Now finding walks of length: " << walkLength << "\n";
	Matrix<double> mat = _adjMat;
	for (int i = 0;i < walkLength - 1;++i) {
		Matrix<double> temp = mat * _adjMat;
		mat = temp;
	}
	// update the newest matrix
	_walkMat = mat;
	// print the walks
	printWalkMat(walkLength);
}

void WalkCounter::promptStats() {
	std::cout << "Here is some info on this current matrix: \n";
	bool running = true;
	while (running) {
		std::cout << "Enter: \n";
		std::cout << "1. Determinant\n2. Cofactor Matrix\n3. Inverse Matrix\n\"q\" to quit.\n";
		std::string ui;
		std::cin >> ui;
		if (ui == "q") {
			running = false;
			break;
		}
		int choice = std::atoi(ui.c_str());
		
		switch (choice) {
		case 1:
		{
			double det;
			det = _walkMat.getDet();
			std::cout << "The determinant is: " << det << ". \n";
			break;
		}
		case 2: {
			Matrix<double> cofactorMat = _walkMat.cofactorMatrix();
			std::cout << "The cofactor matrix is: \n";
			cofactorMat.print();
			break;
		}
		case 3: {
			Matrix<double> inverseMat = _walkMat.invert();
			if (inverseMat.getSize() == 1 && inverseMat.getAtIndex(0) == 0) {
				std::cout << "The matrix was singular. No inverse.\n";
			}
			else {
				std::cout << "The inverse matrix is: \n";
				inverseMat.print();
				std::cout << "Multiplying by the original matrix: \n";
				Matrix<double> identity = _walkMat * inverseMat;
				identity.print();
			}
			break;
		}
		default: {
			std::cout << "Try again.\n";
		}
		}
	}
}
void WalkCounter::printAdjMat() {
	std::cout << "The adjacency matrix is:\n";
	_adjMat.print();
}

void WalkCounter::printWalkMat(int walks) {
	std::cout << "The walks of count " << walks << " look like:\n";
	_walkMat.print();
}

void WalkCounter::printVertices() {
	std::cout << "Here are all the vertices and their connections:\n";
	for (size_t i = 0;i < _vertices.size();++i) {
		std::cout << "Vertex " << i + 1<< "\n";
		std::cout << "Connections: " << "\n";
		for (int j = 0;j < _vertices[i]._edges.size();j++) {
			std::cout << _vertices[i]._edges[j] << " ";
		}
		std::cout << "\n";
	}
}








