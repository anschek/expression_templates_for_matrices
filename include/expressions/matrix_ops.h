//
// Created by anschek on 20.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_OPS_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_OPS_H
#include <iostream>

template<typename Derived, typename T> class MatrixExpr;

template<typename LHS, typename RHS, typename T>
class AddExpr : public MatrixExpr<AddExpr<LHS, RHS, T>, T> {
public:
	AddExpr(const LHS &lhs, const RHS &rhs);
	size_t rows() const;
	size_t cols() const;
	T operator()(size_t i, size_t j) const;

private:
	const LHS &lhs_;
	const RHS &rhs_;
};
#include "add_expr.tpp"

template<typename LHS, typename RHS, typename T>
class SubExpr : public MatrixExpr<SubExpr<LHS, RHS, T>, T> {
public:
	SubExpr(const LHS &lhs, const RHS &rhs);
	size_t rows() const;
	size_t cols() const;
	T operator()(size_t i, size_t j) const;

private:
	const LHS &lhs_;
	const RHS &rhs_;
};
#include "sub_expr.tpp"

template<typename E, typename T>
class ScalarMultExpr : public MatrixExpr<ScalarMultExpr<E, T>, T> {
public:
	ScalarMultExpr(const E &expr, T alpha);
	size_t rows() const;
	size_t cols() const;
	T operator()(size_t i, size_t j) const;

private:
	const E &expr_;
	const T alpha_;
};
#include "scalar_mult_expr.tpp"

#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_OPS_H
