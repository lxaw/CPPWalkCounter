/*
Written (with love) by Lex Whalen
*/

#include <iostream>

#include "Matrix.h"
#include "Matrix.cpp"

int main()
{
	Matrix<int> mat{ 2,5};
	mat.setRandomInt();
	mat.print();
//	Matrix<int> T = mat.transpose();
//	T.print();
//
//	mat* T;
	Matrix<int> mat2{ 5,1 };
	mat2.setRandomInt();
	mat2.print();
	mat* mat2;
}

