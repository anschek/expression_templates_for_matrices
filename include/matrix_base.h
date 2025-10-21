//
// Created by anschek on 20.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H

#include "expressions/matrix_ops.h"

template<typename Derived, typename T>
class MatrixExpr {
public:
	size_t rows() const;
	size_t cols() const;
	T operator()(size_t i, size_t j) const;
	template<typename Other> AddExpr<Derived,Other,T> operator+(const MatrixExpr<Other, T> &other) const;
	template<typename Other> SubExpr<Derived,Other,T> operator-(const MatrixExpr<Other, T> &other) const;
	ScalarMultExpr<Derived,T> operator*(double alpha) const;
	TransposeExpr<Derived,T> transpose() const;
	template<typename Other> MultExpr<Derived, Other, T> operator*(const MatrixExpr<Other, T> &other) const;
};

#include "matrix_base.tpp"
#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H
