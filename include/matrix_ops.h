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

template<typename LHS, typename RHS, typename T>
AddExpr<LHS, RHS, T>::AddExpr(const LHS &lhs, const RHS &rhs) : lhs_(lhs), rhs_(rhs) {
	if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())
		throw std::invalid_argument("Matrix dimensions do not match");
}

template<typename LHS, typename RHS, typename T>
size_t AddExpr<LHS, RHS, T>::rows() const {
	return lhs_.rows();
}

template<typename LHS, typename RHS, typename T>
size_t AddExpr<LHS, RHS, T>::cols() const {
	return lhs_.cols();
}

template<typename LHS, typename RHS, typename T>
T AddExpr<LHS, RHS, T>::operator()(size_t i, size_t j) const {
	std::cout << "AddExpr::operator() -> computing (" << i << ", " << j << ")\n";
	return lhs_(i, j) + rhs_(i, j);
}

template<typename LHS, typename RHS, typename T>
SubExpr<LHS, RHS, T>::SubExpr(const LHS &lhs, const RHS &rhs): lhs_(lhs), rhs_(rhs) {
	if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())
		throw std::invalid_argument("Matrix dimensions do not match");
}

template<typename LHS, typename RHS, typename T>
size_t SubExpr<LHS, RHS, T>::rows() const {
	return lhs_.rows();
}

template<typename LHS, typename RHS, typename T>
size_t SubExpr<LHS, RHS, T>::cols() const {
	return lhs_.cols();
}

template<typename LHS, typename RHS, typename T>
T SubExpr<LHS, RHS, T>::operator()(size_t i, size_t j) const {
	std::cout << "SubExpr::operator() -> computing (" << i << ", " << j << ")\n";
	return lhs_(i, j) - rhs_(i, j);
}

template<typename E, typename T>
ScalarMultExpr<E, T>::ScalarMultExpr(const E &expr, T alpha): expr_(expr), alpha_(alpha) {
}

template<typename E, typename T>
size_t ScalarMultExpr<E, T>::rows() const {
	return expr_.rows();
}

template<typename E, typename T>
size_t ScalarMultExpr<E, T>::cols() const {
	return expr_.cols();
}

template<typename E, typename T>
T ScalarMultExpr<E, T>::operator()(size_t i, size_t j) const {
	std::cout << "ScalarMultExpr::operator() -> computing (" << i << ", " << j << ")\n";
	return expr_(i, j) * alpha_;
}

#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_OPS_H
