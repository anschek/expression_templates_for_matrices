//
// Created by anschek on 20.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H

#include "expressions/elementwise_expr.h"
#include "expressions/elementwise_ops.h"
#include "expressions/scalar_mult_expr.h"
#include "expressions/transpose_expr.h"
#include "expressions/mult_expr.h"
#include <cmath>

template<typename Derived, Arithmetic T>
class MatrixExpr {
public:
	using value_type = T;
	size_t rows() const;
	size_t cols() const;
	T operator()(size_t i, size_t j) const;
	template<typename OtherDerived, Arithmetic OtherT> ElementwiseExpr<Derived,OtherDerived, AddOp> operator+(const MatrixExpr<OtherDerived, OtherT> &other) const;
	template<typename OtherDerived, Arithmetic OtherT> ElementwiseExpr<Derived,OtherDerived, SubOp> operator-(const MatrixExpr<OtherDerived, OtherT> &other) const;
	template<Arithmetic ScalarT>ScalarMultExpr<Derived,ScalarT> operator*(ScalarT alpha) const;
	TransposeExpr<Derived,T> transpose() const;
	template<typename OtherDerived, Arithmetic OtherT> MultExpr<Derived, OtherDerived> operator*(const MatrixExpr<OtherDerived, OtherT> &other) const;
	template<typename OtherDerived, Arithmetic OtherT> bool operator==(const MatrixExpr<OtherDerived, OtherT> &other) const;
};

// ---DEFINITION---

template<typename Derived, Arithmetic T>
size_t MatrixExpr<Derived, T>::rows() const {
	return static_cast<const Derived &>(*this).rows();
}

template<typename Derived, Arithmetic T>
size_t MatrixExpr<Derived, T>::cols() const {
	return static_cast<const Derived &>(*this).cols();
}

template<typename Derived, Arithmetic T>
T MatrixExpr<Derived, T>::operator()(size_t i, size_t j) const {
	return static_cast<const Derived &>(*this)(i, j);
}

template<typename Derived, Arithmetic T>
template<typename OtherDerived, Arithmetic OtherT>
ElementwiseExpr<Derived,OtherDerived, AddOp> MatrixExpr<Derived, T>::operator+(const MatrixExpr<OtherDerived, OtherT> &other) const {
	return ElementwiseExpr<Derived,OtherDerived, AddOp>(static_cast<const Derived &>(*this),
								static_cast<const OtherDerived &>(other));
}

template<typename Derived, Arithmetic T>
template<typename OtherDerived, Arithmetic OtherT>
ElementwiseExpr<Derived,OtherDerived, SubOp> MatrixExpr<Derived, T>::operator-(const MatrixExpr<OtherDerived, OtherT> &other) const {
	return ElementwiseExpr<Derived,OtherDerived, SubOp>(static_cast<const Derived &>(*this),
								static_cast<const OtherDerived &>(other));
}

template<typename Derived, Arithmetic T>
template<Arithmetic ScalarT>
ScalarMultExpr<Derived, ScalarT> MatrixExpr<Derived, T>::operator*(ScalarT alpha) const {
	return ScalarMultExpr<Derived, ScalarT>(static_cast<const Derived &>(*this), alpha);
}

template<typename Derived, Arithmetic T>
TransposeExpr<Derived, T> MatrixExpr<Derived, T>::transpose() const {
	return TransposeExpr<Derived, T>(static_cast<const Derived &>(*this));
}

template<typename Derived, Arithmetic T>
template<typename OtherDerived, Arithmetic OtherT>
MultExpr<Derived, OtherDerived> MatrixExpr<Derived, T>::operator*(const MatrixExpr<OtherDerived, OtherT> &other) const {
	return MultExpr<Derived, OtherDerived>(static_cast<const Derived &>(*this),
										static_cast<const OtherDerived &>(other));
}

template<typename Derived, Arithmetic T>
template<typename OtherDerived, Arithmetic OtherT>
bool MatrixExpr<Derived, T>::operator==(const MatrixExpr<OtherDerived, OtherT> &other) const {
	if (this->rows() != other.rows() || this->cols() != other.cols())
		return false;
	for (size_t i = 0; i < this->rows(); ++i)
		for (size_t j = 0; j < this->cols(); ++j)
			if (std::fabs(this->operator()(i, j) - other(i, j)) > 1e-6)
				return false;
	return true;
}
#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H
