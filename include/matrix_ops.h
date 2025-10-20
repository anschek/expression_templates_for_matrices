//
// Created by anschek on 20.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_OPS_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_OPS_H
#include <iostream>

template<typename Derived, typename T>
class MatrixExpr;

template<typename LHS, typename RHS, typename T>
class AddExpr;

template<typename LHS, typename RHS, typename T>
class AddExpr : public MatrixExpr<AddExpr<LHS, RHS, T>, T> {
public:
	AddExpr(const LHS &lhs, const RHS &rhs) : lhs_(lhs), rhs_(rhs) {
	}

	size_t rows() const { return lhs_.rows(); }
	size_t cols() const { return lhs_.cols(); }

	T operator()(size_t i, size_t j) const {
		std::cout << "AddExpr::operator() -> computing (" << i << ", " << j << ")\n";
		return lhs_(i, j) + rhs_(i, j);
	}

private:
	const LHS &lhs_;
	const RHS &rhs_;
};

#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_OPS_H
