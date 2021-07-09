/*
Written (with love) by Lex Whalen
*/

#include <iostream>

#include "Matrix.h"
#include "Matrix.cpp"

int main()
{
	Matrix<int> mat{4,4};
	mat.setRandomInt();
	mat.print();

	mat.getDet();
}

