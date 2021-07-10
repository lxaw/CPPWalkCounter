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
	
	// get the index conversion from row, col
	int getIndexFromRowCol(int row, int col);
	// get the row from vector index
	int getRowFromIndex(int index);
	// get the col from vector index
	int getColFromIndex(int index);
/*    Methods to change the values of the matrix itself     */

	// set a value at index
	void setAtRowCol(T value, int row, int col);

	T getAtRowCol(int row, int col);

	int getRows() const;
	int getCols() const;

	int getSize() const;

	T getAtIndex(int index) const;
	void setAtIndex(T value,int index);

	T getCofactor(int row, int col);
	T getDet();

	Matrix<T> cofactorMatrix();
	
	// returns the inverse matrix via cofactors
	Matrix<T> invert();



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
	
	std::vector<T> getMat();


	void print() const;
		

private:
	std::vector<T> _mat;

	T getDet(std::vector<T> matVec,int rows, int cols,int multiplier);

	int _rows = 0;
	int _cols = 0;
	
};

