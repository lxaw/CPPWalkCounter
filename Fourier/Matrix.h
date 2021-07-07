/*
Written (with love) by Lex Whalen
*/
#pragma once

#include <vector>

template <class T>
class Matrix
{
public:
	Matrix(int rows, int cols);
	
/*    Methods to change the values of the matrix itself     */

	// initializes the matrix by setting all vals to zero
	void resetVec();
	// sets a bunch of random integers (0-9)
	void setRandomInt();
	// sets the identity matrix
	void setIdentity();
	
/*    Matrix operations    */

	// mat mult
	Matrix<T> operator*(const Matrix<T>& aMatrix);
	// transpose
	Matrix<T> transpose();
	// inverse of mat -- this time using Cramer's rule
	Matrix<T> inverse();


	void print();
	

private:
	std::vector<T> _mat;

	int _rows = 0;
	int _cols = 0;
	
};

