//
// Created by anschek on 22.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_DIAGONAL_MATRIX_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_DIAGONAL_MATRIX_H
#include <vector>

#include "matrix_base.h"

template<Arithmetic T>
class DiagonalMatrix: public MatrixExpr<DiagonalMatrix<T>,T> {
public:
	using value_type = T;
	DiagonalMatrix(std::initializer_list<T> data);
	size_t rows() const;
	size_t cols() const;
	T operator()(size_t i, size_t j) const;

private:
	std::vector<T> data_;
	size_t n_;
};

// ---DEFINITION---

template<Arithmetic T>
DiagonalMatrix<T>::DiagonalMatrix(std::initializer_list<T> data) {
	n_ = data.size();
	data_.reserve(n_);
	data_.insert(data_.end(), data.begin(), data.end());
}

template<Arithmetic T>
size_t DiagonalMatrix<T>::rows() const {
	return n_;
}

template<Arithmetic T>
size_t DiagonalMatrix<T>::cols() const {
	return n_;
}

template<Arithmetic T>
T DiagonalMatrix<T>::operator()(size_t i, size_t j) const {
	if (i >= n_ || j >= n_) {
		throw std::out_of_range("Matrix index out of range");
	}
	return i==j? data_[i] : 0;
}
#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_DIAGONAL_MATRIX_H
