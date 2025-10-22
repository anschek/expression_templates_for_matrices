//
// Created by anschek on 22.10.2025.
//

#include "matrices/zero_matrix.h"

ZeroMatrix::ZeroMatrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
}

size_t ZeroMatrix::rows() const {
	return rows_;
}

size_t ZeroMatrix::cols() const {
	return cols_;
}

int ZeroMatrix::operator()(size_t i, size_t j) const {
	if (i >= rows_ || j >= cols_) {
		throw std::out_of_range("Matrix index out of range");
	}
	return 0;
}