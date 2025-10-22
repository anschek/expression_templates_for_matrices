//
// Created by anschek on 22.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_DETERMINANT_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_DETERMINANT_H
#include <cmath>
#include "matrix_base.h"
#include "matrices/matrix.h"
#include "lu_decompose.h"

namespace analysis {

template<Arithmetic T> double determinant_lu(Matrix<T> A);

// ---DEFINITION---

template<Arithmetic T>
double determinant_lu(Matrix<T> A) {
	const size_t n = A.rows();
	if (A.cols() != n)
		throw std::invalid_argument("Matrix must be square");

	if (!lu_decompose(A))
		return T{};

	T det = 1;
	for (size_t i = 0; i < n; ++i)
		det *= A(i, i); // диагональ U
	return det;
}
} // namespace analysis

#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_DETERMINANT_H