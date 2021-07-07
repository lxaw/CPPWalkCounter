/*
Written (with love) by Lex Whalen
*/

#include <iostream>

#include "Matrix.h"
#include "Matrix.cpp"

int main()
{
	std::cout << "3x5 matrix with random entries\n";
	Matrix<int> m{3,5};
	m.setRandomInt();
	m.print();

	std::cout << "Setting the identity matrix on a 4x4\n";
	Matrix<int> m3{ 4,4 };
	m3.setIdentity();
	m3.print();
}

