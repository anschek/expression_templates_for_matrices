//
// Created by anschek on 20.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H

#include "matrix_ops.h"

template<typename Derived, typename T>
class MatrixExpr {
public:
	size_t rows() const;
	size_t cols() const;
	T operator()(size_t i, size_t j) const;
	template<typename Other> AddExpr<Derived,Other,T> operator+(const MatrixExpr<Other, T> &other) const;
	template<typename Other> SubExpr<Derived,Other,T> operator-(const MatrixExpr<Other, T> &other) const;
	ScalarMultExpr<Derived,T> operator*(double alpha) const;

};

template<typename Derived, typename T>
size_t MatrixExpr<Derived, T>::rows() const {
	return static_cast<const Derived &>(*this).rows();
}

template<typename Derived, typename T>
size_t MatrixExpr<Derived, T>::cols() const {
	return static_cast<const Derived &>(*this).cols();
}

template<typename Derived, typename T>
T MatrixExpr<Derived, T>::operator()(size_t i, size_t j) const {
	return static_cast<const Derived &>(*this)(i, j);
}

template<typename Derived, typename T>
template<typename Other>
AddExpr<Derived,Other,T> MatrixExpr<Derived, T>::operator+(const MatrixExpr<Other, T> &other) const {
		return AddExpr<Derived, Other, T>(static_cast<const Derived &>(*this),
										static_cast<const Other &>(other));
}

template<typename Derived, typename T>
template<typename Other>
SubExpr<Derived, Other, T> MatrixExpr<Derived, T>::operator-(const MatrixExpr<Other, T> &other) const {
	return SubExpr<Derived, Other, T>(static_cast<const Derived &>(*this),
								static_cast<const Other &>(other));
}

template<typename Derived, typename T>
ScalarMultExpr<Derived, T> MatrixExpr<Derived, T>::operator*(double alpha) const {
	return ScalarMultExpr<Derived, T>(static_cast<const Derived &>(*this), alpha);
}
#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H
