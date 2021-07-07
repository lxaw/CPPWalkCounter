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

	for (int i = 0;i < _rows * _cols;i++) {
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
		int curr_row = i / _cols;
		int pos_in_row = (i % _cols);
		if (curr_row == pos_in_row) {
			_mat[i] = 1;
		}
		else {
			_mat[i] = 0;
		}
	}
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


