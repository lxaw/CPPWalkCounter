/*
Written (with love) by Lex Whalen
*/
#include <iostream>
#include <assert.h>
#include <random>
#include <math.h>



#include "Matrix.h"


template <class T>
Matrix<T>::Matrix(int rows, int cols) {
	// use strides to represent 2d mat in 1d
	assert(rows > 0 && cols > 0);

	_rows = rows;
	_cols = cols;

	resetVec();
}

// reset vectors
template <class T>
void Matrix<T>::resetVec() {
	/*
	This function resets a vector by clearing it and then putting zeroes in for the correct
	amount of space held by the matrix. Not sure if vectors automatically store zeros, but we will see!
	*/
	assert(_rows > 0 && _cols > 0);
	
	// check if vec already empty
	if (!_mat.empty()) {
		_mat.clear();
	}

	for (int i = 0;i < _rows * _cols;++i) {
		_mat.push_back(0);
	}
}

// set the matrix to random integer values
template <class T>
void Matrix<T>::setRandomInt() {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, 9);
	for (size_t i = 0, ilen = _mat.size();i < ilen;++i) {
		_mat[i] = uni(rng);
	}
}

// set the matrix to identity
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

// gt the index from row, col form
template <class T>
int Matrix<T>::getIndexFromRowCol(int row, int col) {
	// returns the correct index of the vector given row, col
	return ((row * _mat.size() / _rows) + col);
}

// get the row from vector index
template <class T>
int Matrix<T>::getRowFromIndex(int index) {
	// returns the matrix row from the index of a vector
	return index / _cols;
}

// get the col from vector index
template <class T>
int Matrix<T>::getColFromIndex(int index) {
	// returns the matrix row from the index of a vector
	return index % _cols;
}

// set a value at row, col
template <class T>
void Matrix<T>::setAtRowCol(T value,int row, int col) {
	int conversion = getIndexFromRowCol(row, col);
	_mat[conversion] = value;
}

// get a value at row, co
template <class T>
T Matrix<T>::getAtRowCol(int row, int col) {
	assert(row + col < _mat.size());

	int conversion = getIndexFromRowCol(row, col);

	return _mat[conversion];
}

// get a value given an index
template <class T>
T Matrix<T>::getAtIndex(int index) const {
	size_t size = _mat.size();
	assert(index < size);
	return _mat[index];
}

// set a value given an index
template <class T>
void Matrix<T>::setAtIndex(T value, int index) {
	size_t size = _mat.size();
	assert(index < _mat.size());
	
	_mat[index] = value;
}

// get the columns of the matrix
template <class T>
int Matrix<T>::getCols() const{
	return _cols;
}

// get the rows of the matrix
template <class T>
int Matrix<T>::getRows() const {
	return _rows;
}

// get the size of the vector of the matrix
template <class T>
int Matrix<T>::getSize() const {
	return _mat.size();
}

// get the matrix vector
template <class T>
std::vector<T> Matrix<T>::getMat() {
	return _mat;
}
/***************************Common operations*******************************/
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
	/*
	This function performs matrix multiplication.
	*/
	assert(_cols == aMatrix.getRows());

	Matrix<T> newMat{ _rows,aMatrix.getCols()};

	for (size_t i = 0, ilen = newMat.getSize();i < ilen;++i) {
		T dotProd = 0;
		int currRow = newMat.getRowFromIndex(i);
		int currCol = newMat.getColFromIndex(i);

		for (size_t j = 0, jlen = _cols;j < jlen;++j) {
			int lMat_index = currRow * _cols + j;
			int rMat_index = currCol + (aMatrix.getCols() * j);

			T lMat_val = _mat[lMat_index];
			T rMat_val = aMatrix.getAtIndex(rMat_index);

//			std::cout << lMat_index << " "<< _mat[lMat_index] << "\n";
//			std::cout << rMat_index << "-> " << aMatrix.getAtIndex(rMat_index) << "\n";
			dotProd += (lMat_val * rMat_val);
		}

		
		newMat.setAtRowCol(dotProd, currRow, currCol);
	}
	return newMat;
}

template <class T>
T Matrix<T>::getDet() {
	// we use det by cofactors here
	return getDet(_mat, _rows, _cols,1);

}

template <class T>
T Matrix<T>::getDet(std::vector<T> vecMat,int rows, int cols, double multiplier) {
	/*
	Recursive method that gets the determinant of a matrix by splitting it up and getting determinants of the sub matrices
	Stops with the size of the matrix is 1x1.

	Represents the matrix by using a vector "vecMat".
	*/
	if (vecMat.size() == 1) {
		return multiplier * vecMat[0];
	}
	T det = 0;
	
	std::vector<std::vector<T>>  subVecMats;
	for (int i = 0;i < cols;++i){
		std::vector<T> subVec;
		Matrix<T> subMat{ rows - 1,cols - 1 };
		for (size_t j = cols, jlen = vecMat.size();j < jlen;++j) {
			if (j% cols != i) {
				/*
				Splitting up the matrix into sections and getting the dets
				See Gilbert Strang's chapter on determinates in his Linear Algebra book.
				*/
				subVec.push_back(vecMat[j]);
			}
		}
		subVecMats.push_back(subVec);
	}
	for (size_t i = 0, ilen = subVecMats.size();i < ilen;++i) {
		std::vector<T> v = subVecMats[i];
//		for (int j = 0, jlen = v.size();j < jlen;j++) {
//			if (j % (cols - 1) == 0) {
//				std::cout << "\n";
//			}
//			std::cout << v[j] << ",";
//		}
//		std::cout << "\n";
		T newMultiplier = multiplier * vecMat[i];
		if (i % 2 == 1) {
		// if odd, give negative
			newMultiplier = newMultiplier * -1;
		}
//		std::cout << "mult: " << newMultiplier << "\n";
		det += getDet(v,rows-1,cols-1,newMultiplier);
	}

	return det;
}

template <class T>
T Matrix<T>::getCofactor(int row, int col) {
	/*
	Returns the cofactor of a specific row, col
	Cofactors are dets of size n-1
	*/
	std::vector<T> subVecMat;

	for (size_t i = 0, ilen = _mat.size();i < ilen;++i) {
		if (getRowFromIndex(i) != row && getColFromIndex(i) != col) {
			subVecMat.push_back(_mat[i]);
		}
	}
	T detCofactor = getDet(subVecMat, _rows-1, _cols-1, 1);

	return detCofactor;
}

template <class T>
Matrix<T> Matrix<T>::cofactorMatrix() {
	/*
	Iterates through matrix, gets cofactors of each index, populates a matrix and returns it.
	*/
	assert(_rows == _cols);

	Matrix<T> cofactorMat{ _rows,_cols };

	for(size_t i = 0, ilen = _mat.size();i < ilen;++i) {
		int curRow = getRowFromIndex(i);
		int curCol = getColFromIndex(i);
		T cofactor = getCofactor(curRow, curCol);
		if ((curRow + curCol) % 2 != 0) {
			cofactor *= -1;
		}
		cofactorMat.setAtRowCol(cofactor, curRow, curCol);
	}

	return cofactorMat;
}

template <class T>
Matrix<T> Matrix<T>::invert() {
	assert(_rows == _cols);
	
	T detA = getDet();
	// detA = 0 means no inverse

	if (detA != 0) {
		/*
		The inverse of a matrix is equal to the cofactor matrix's transpose divided by the determinant of the matrix.
		*/
		Matrix<T> cofactorMat = cofactorMatrix();
		
		Matrix<T> cofactorMatT = cofactorMat.transpose();

		for (size_t i = 0, ilen = _mat.size();i < ilen;++i) {
			T newVal = cofactorMatT.getAtIndex(i) / detA;
			cofactorMatT.setAtIndex(newVal, i);
		}
		return cofactorMatT;
	}
	else {
		// return a zero matrix of size 1x1
		Matrix<T> zeroes { 1,1 };
		return zeroes;
	}

}


/***************************Common operations END*******************************/

template <class T>
void Matrix<T>::print() const{
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


