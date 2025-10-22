//
// Created by anschek on 22.10.2025.
//

#include "matrices/identity_matrix.h"

IdentityMatrix::IdentityMatrix(size_t n): n_(n) {
}

size_t IdentityMatrix::rows() const {
	return n_;
}

size_t IdentityMatrix::cols() const {
	return n_;
}

int IdentityMatrix::operator()(size_t i, size_t j) const {
	if (i >= n_ || j >= n_) {
		throw std::out_of_range("Matrix index out of range");
	}
	return i == j ? 1 : 0;
}
