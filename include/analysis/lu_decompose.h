//
// Created by anschek on 22.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_LU_DECOMPOSITION_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_LU_DECOMPOSITION_H
#include <cmath>
#include "matrix_base.h"
#include "matrices/matrix.h"

namespace analysis {

template<Arithmetic T> bool lu_decompose(Matrix<T> &A);
template<Arithmetic T> Matrix<T> extract_L(const Matrix<T>& LU);
template<Arithmetic T> Matrix<T> extract_U(const Matrix<T>& LU);

// ---DEFINITION---

template<Arithmetic T>
bool lu_decompose(Matrix<T>& A) {
	const size_t n = A.rows();
	if (A.cols() != n)
		throw std::invalid_argument("Matrix must be square");

	for (size_t k = 0; k < n; ++k) {
		if (std::abs(A(k, k)) < static_cast<T>(1e-12))
			return false;

		for (size_t i = k + 1; i < n; ++i) {
			T factor = A(i, k) / A(k, k);
			A(i, k) = factor; // store L(i,k)

			for (size_t j = k + 1; j < n; ++j) {
				A(i, j) -= factor * A(k, j);
			}
		}
	}
	return true;
}

template<Arithmetic T>
Matrix<T> extract_L(const Matrix<T>& LU) {
	size_t n = LU.rows();
	Matrix<T> L(n, n, T{0});
	for (size_t i = 0; i < n; ++i) {
		L(i, i) = T{1};
		for (size_t j = 0; j < i; ++j)
			L(i, j) = LU(i, j);
	}
	return L;
}

template<Arithmetic T>
Matrix<T> extract_U(const Matrix<T>& LU) {
	size_t n = LU.rows();
	Matrix<T> U(n, n, T{0});
	for (size_t i = 0; i < n; ++i)
		for (size_t j = i; j < n; ++j)
			U(i, j) = LU(i, j);
	return U;
}

} // namespace analysis
#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_LU_DECOMPOSITION_H