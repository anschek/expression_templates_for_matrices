//
// Created by anschek on 22.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_NORMS_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_NORMS_H
#include "matrix_base.h"
#include <cmath>

namespace analysis {

template<typename Expr, Arithmetic T> T norm1(const MatrixExpr<Expr, T>& expr);
template<typename Expr, Arithmetic T> T normInf(const MatrixExpr<Expr, T>& expr);
template<typename Expr, Arithmetic T> double normFrobenius(const MatrixExpr<Expr, T>& expr);

// ---DEFINITION---

template<typename Expr, Arithmetic T>
T norm1(const MatrixExpr<Expr, T> &expr) {
	T max_sum{};
	for (size_t j = 0; j < expr.cols(); ++j) {
		T sum{};
		for (size_t i = 0; i < expr.rows(); ++i)
			sum += std::fabs(expr(i, j));
		max_sum = std::max(max_sum, sum);
	}
	return max_sum;
}

template<typename Expr, Arithmetic T>
T normInf(const MatrixExpr<Expr, T> &expr) {
	T max_sum{};
	for (size_t i = 0; i < expr.rows(); ++i) {
		T sum{};
		for (size_t j = 0; j < expr.cols(); ++j)
			sum += std::fabs(expr(i, j));
		max_sum = std::max(max_sum, sum);
	}
	return max_sum;
}

template<typename Expr, Arithmetic T>
double normFrobenius(const MatrixExpr<Expr, T> &expr) {
	double sum{};
	for (size_t i = 0; i < expr.rows(); ++i)
		for (size_t j = 0; j < expr.cols(); ++j)
			sum += std::pow(expr(i, j), 2);
	return std::sqrt(sum);
}
} //namespace analysis

#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_NORMS_H