//
// Created by anschek on 20.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H

#include "matrix_ops.h"

template<typename Derived, typename T>
class MatrixExpr {
public:
	size_t rows() const { return static_cast<const Derived &>(*this).rows(); }
	size_t cols() const { return static_cast<const Derived &>(*this).cols(); }

	T operator()(size_t i, size_t j) const {
		return static_cast<const Derived &>(*this)(i, j);
	}

	template<typename Other>
	auto operator+(const MatrixExpr<Other, T> &other) const {
		return AddExpr<Derived, Other, T>(static_cast<const Derived &>(*this),
										static_cast<const Other &>(other));
	}
};
#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_BASE_H
