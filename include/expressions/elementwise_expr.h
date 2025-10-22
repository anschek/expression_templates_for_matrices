//
// Created by anschek on 22.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_ELEMENTWISE_EXPR_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_ELEMENTWISE_EXPR_H
#include <iostream>
#include <stdexcept>
#include "concepts.h"
template<typename Derived, Arithmetic T> class MatrixExpr;

// expression for sequential modification of elements with same object creation check and dimension
template<typename LHS, typename RHS, typename Op>
class ElementwiseExpr : public MatrixExpr<ElementwiseExpr<LHS, RHS, Op>, common_value_t<LHS, RHS>> {
public:
	using value_type = common_value_t<LHS, RHS>;
	ElementwiseExpr(const LHS &lhs, const RHS &rhs);
	size_t rows() const;
	size_t cols() const;
	value_type operator()(size_t i, size_t j) const;

private:
	const LHS &lhs_;
	const RHS &rhs_;
};

// ---DEFINITION---

template<typename LHS, typename RHS, typename Op>
ElementwiseExpr<LHS, RHS, Op>::ElementwiseExpr(const LHS &lhs, const RHS &rhs): lhs_(lhs), rhs_(rhs) {
	if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())
		throw std::invalid_argument("Matrix dimensions do not match");
}

template<typename LHS, typename RHS, typename Op>
size_t ElementwiseExpr<LHS, RHS, Op>::rows() const {
	return lhs_.rows();
}

template<typename LHS, typename RHS, typename Op>
size_t ElementwiseExpr<LHS, RHS, Op>::cols() const {
	return lhs_.cols();
}

template<typename LHS, typename RHS, typename Op>
ElementwiseExpr<LHS, RHS, Op>::value_type ElementwiseExpr<LHS, RHS, Op>::operator()(size_t i, size_t j) const {
	std::cout << Op::name << "::operator() -> computing (" << i << ", " << j << ")\n";
	return Op{}(lhs_(i,j), rhs_(i,j));
}
#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_ELEMENTWISE_EXPR_H
