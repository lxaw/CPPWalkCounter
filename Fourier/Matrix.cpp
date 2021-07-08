/*
Written (with love) by Lex Whalen
*/
#include <iostream>
#include <assert.h>
#include <random>


#include "Matrix.h"


template <class T>
Matrix<T>::Matrix(int rows, int cols) {
	// use strides to represent 2d mat in 1d
	assert(rows > 0 && cols > 0);

	_rows = rows;
	_cols = cols;

	resetVec();
}

template <class T>
void Matrix<T>::resetVec() {
	assert(_rows > 0 && _cols > 0);
	
	// check if vec already empty
	if (!_mat.empty()) {
		_mat.clear();
	}

	for (int i = 0;i < _rows * _cols;++i) {
		_mat.push_back(0);
	}
}

template <class T>
void Matrix<T>::setRandomInt() {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, 9);
	for (size_t i = 0, ilen = _mat.size();i < ilen;++i) {
		_mat[i] = uni(rng);
	}
}

template <class T>
void Matrix<T>::setIdentity() {
	assert(_rows = _cols);

	for (size_t i = 0, ilen = _mat.size();i < ilen;++i) {
		int curr_row = getRowFromIndex(i);
		int curr_col = getColFromIndex(i);
		if (curr_row == curr_col) {
			_mat[i] = 1;
		}
		else {
			_mat[i] = 0;
		}
	}
}

template <class T>
int Matrix<T>::getIndexFromRowCol(int row, int col) {
	// returns the correct index of the vector given row, col
	return ((row * _mat.size() / _rows) + col);
}
template <class T>
int Matrix<T>::getRowFromIndex(int index) {
	// returns the matrix row from the index of a vector
	return index / _cols;
}

template <class T>
int Matrix<T>::getColFromIndex(int index) {
	// returns the matrix row from the index of a vector
	return index % _cols;
}


template <class T>
void Matrix<T>::setAtRowCol(T value,int row, int col) {
	int conversion = getIndexFromRowCol(row, col);
	_mat[conversion] = value;
}

template <class T>
T Matrix<T>::getAtRowCol(int row, int col) {
	assert(row + col < _mat.size());

	int conversion = getIndexFromRowCol(row, col);

	return _mat[conversion];
}

template <class T>
T Matrix<T>::getAtIndex(int index) const {
	assert(index < _mat.size());
	return _mat[index];
}

template <class T>
int Matrix<T>::getCols() const{
	return _cols;
}

template <class T>
int Matrix<T>::getRows() const {
	return _rows;
}

template <class T>
int Matrix<T>::getSize() const {
	return _mat.size();
}

template <class T>
Matrix<T> Matrix<T>::transpose() {
	Matrix<T> newMat{ _cols,_rows };

	// loop through, flip i and j
	for (size_t i = 0, ilen = _mat.size();i < ilen;++i) {
		int oldMat_curRow = getRowFromIndex(i);
		int oldMat_curCol = getColFromIndex(i);

		newMat.setAtRowCol(getAtRowCol(oldMat_curRow, oldMat_curCol), oldMat_curCol, oldMat_curRow);
	}

	return newMat;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& aMatrix) {
	assert(_cols == aMatrix.getRows());

	Matrix<T> newMat{ _rows,aMatrix.getCols()};

	for (size_t i = 0, ilen = newMat.getSize();i < ilen;++i) {
		int dotProd = 0;
		int currRow = newMat.getRowFromIndex(i);
		int currCol = newMat.getColFromIndex(i);

		for (size_t j = 0, jlen = _cols;j < jlen;++j) {
			int lMat_index = currRow * _cols + j;
			int rMat_index = currCol + (aMatrix.getCols() * j);

			int lMat_val = _mat[lMat_index];
			int rMat_val = aMatrix.getAtIndex(rMat_index);

//			std::cout << lMat_index << " "<< _mat[lMat_index] << "\n";
//			std::cout << rMat_index << "-> " << aMatrix.getAtIndex(rMat_index) << "\n";
			dotProd += (lMat_val * rMat_val);
		}


		newMat.setAtRowCol(dotProd, currRow, currCol);
	}

	newMat.print();

	return newMat;
}

template <class T>
void Matrix<T>::print() {
	assert(_rows > 0 && _cols > 0);
	
	for (size_t i = 0,ilen=_mat.size();i < ilen;++i) {
		if (i % _cols == 0) {
			std::cout << "\n[ ";
		}
		std::cout << _mat[i];
		
		if (i%_cols == _cols - 1) {
			std::cout << " ]";
		}
		else {
			std::cout << " , ";
		}
	}
	std::cout << "\n\n";
}


