/*
Written (with love) by Lex Whalen
*/

#include <iostream>

#include "Matrix.h"
#include "Matrix.cpp"

int main()
{
	Matrix<double> mat{3,3};
	mat.setRandomInt();

	std::cout << "Original matrix:" << "\n";
	mat.print();

	std::cout << "Determinant: " << "\n";
	std::cout << mat.getDet() << "\n";

	std::cout << "Cofactor matrix: " << "\n";
	mat.cofactorMatrix().print();

	Matrix<double> inverse = mat.invert();

	std::cout << "Inverted matrix:" << "\n";
	inverse.print();
}

