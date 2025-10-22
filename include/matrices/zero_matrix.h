//
// Created by anschek on 22.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_ZERO_MATRIX_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_ZERO_MATRIX_H
#include "matrix_base.h"

class ZeroMatrix : public MatrixExpr<ZeroMatrix, int> {
public:
	using value_type = int;
	ZeroMatrix(size_t rows, size_t cols);
	size_t rows() const;
	size_t cols() const;
	int operator()(size_t i, size_t j) const;

private:
	size_t rows_, cols_;
};
#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_ZERO_MATRIX_H
