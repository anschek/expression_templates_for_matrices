//
// Created by anschek on 22.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_IDENTITY_MATRIX_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_IDENTITY_MATRIX_H
#include "matrix_base.h"

class IdentityMatrix : public MatrixExpr<IdentityMatrix, int> {
public:
	using value_type = int;
	IdentityMatrix(size_t n);
	size_t rows() const;
	size_t cols() const;
	int operator()(size_t i, size_t j) const;

private:
	size_t n_;
};
#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_IDENTITY_MATRIX_H