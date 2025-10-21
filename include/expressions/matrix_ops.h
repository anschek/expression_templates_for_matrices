//
// Created by anschek on 20.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_OPS_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_OPS_H
#include <iostream>

template<typename T>
concept Arithmetic = std::is_arithmetic_v<std::remove_cvref_t<T>>;

template<typename LHS, typename RHS>
using common_value_t = std::common_type_t<
	typename std::remove_cvref_t<LHS>::value_type,
	typename std::remove_cvref_t<RHS>::value_type
>;

template<typename Derived, Arithmetic T> class MatrixExpr;

template<typename LHS, typename RHS>
class AddExpr : public MatrixExpr<AddExpr<LHS, RHS>, common_value_t<LHS, RHS>> {
public:
	using value_type = common_value_t<LHS, RHS>;

	AddExpr(const LHS &lhs, const RHS &rhs);
	size_t rows() const;
	size_t cols() const;
	value_type operator()(size_t i, size_t j) const;

private:
	const LHS &lhs_;
	const RHS &rhs_;
};
#include "add_expr.tpp"

template<typename LHS, typename RHS>
class SubExpr : public MatrixExpr<SubExpr<LHS, RHS>, common_value_t<LHS, RHS>> {
public:
	using value_type = common_value_t<LHS, RHS>;

	SubExpr(const LHS &lhs, const RHS &rhs);
	size_t rows() const;
	size_t cols() const;
	value_type operator()(size_t i, size_t j) const;

private:
	const LHS &lhs_;
	const RHS &rhs_;
};
#include "sub_expr.tpp"

template<typename E, Arithmetic T>
class ScalarMultExpr : public MatrixExpr<ScalarMultExpr<E, T>, T> {
public:
	using value_type = std::common_type_t<typename std::remove_cvref_t<E>::value_type, T>;
	ScalarMultExpr(const E &expr, T alpha);
	size_t rows() const;
	size_t cols() const;
	T operator()(size_t i, size_t j) const;

private:
	const E &expr_;
	const T alpha_;
};
#include "scalar_mult_expr.tpp"

template<typename E, typename T>
class TransposeExpr : public MatrixExpr<TransposeExpr<E, T>, T> {
public:
	TransposeExpr(const E &expr);
	size_t rows() const;
	size_t cols() const;
	T operator()(size_t i, size_t j) const;

private:
	const E &expr_;
};
#include "transpose_expr.tpp"

template<typename LHS, typename RHS>
class MultExpr : public MatrixExpr<MultExpr<LHS, RHS>, common_value_t<LHS, RHS>> {
public:
	using value_type = common_value_t<LHS, RHS>;

	MultExpr(const LHS &lhs, const RHS &rhs);
	size_t rows() const;
	size_t cols() const;
	value_type operator()(size_t i, size_t j) const;

private:
	const LHS &lhs_;
	const RHS &rhs_;
	size_t n_;
};
#include "mult_expr.tpp"

#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_OPS_H
