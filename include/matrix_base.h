//
// Created by anschek on 20.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H


#include "expressions/matrix_ops.h"

template<typename Derived, Arithmetic T>
class MatrixExpr {
public:
	using value_type = T;
	size_t rows() const;
	size_t cols() const;
	T operator()(size_t i, size_t j) const;
	template<typename OtherDerived, Arithmetic OtherT> AddExpr<Derived,OtherDerived> operator+(const MatrixExpr<OtherDerived, OtherT> &other) const;
	template<typename OtherDerived, Arithmetic OtherT> SubExpr<Derived,OtherDerived> operator-(const MatrixExpr<OtherDerived, OtherT> &other) const;
	ScalarMultExpr<Derived,T> operator*(double alpha) const;
	TransposeExpr<Derived,T> transpose() const;
	template<typename OtherDerived, Arithmetic OtherT> MultExpr<Derived, OtherDerived> operator*(const MatrixExpr<OtherDerived, OtherT> &other) const;
};
#include "matrix_base.tpp"
#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H
