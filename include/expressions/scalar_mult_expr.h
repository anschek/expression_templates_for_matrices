//
// Created by anschek on 20.10.2025.
//
#include <iostream>
#include "concepts.h"
template<typename Derived, Arithmetic T> class MatrixExpr;

// expression for matrix multiplication by scalar
template<typename E, Arithmetic T>
class ScalarMultExpr : public MatrixExpr<ScalarMultExpr<E, T>, common_value_scalar_t<E, T>> {
public:
	using value_type = common_value_scalar_t<E, T>;
	ScalarMultExpr(const E &expr, T alpha);
	size_t rows() const;
	size_t cols() const;
	value_type operator()(size_t i, size_t j) const;

private:
	const E &expr_;
	const T alpha_;
};

// overload for inverse multiplication (if scalar is on left and the matrix is on right, it cannot be implemented inside class, since 'this' is considered first)
template<Arithmetic Scalar, typename E>
requires std::is_base_of_v<MatrixExpr<E, typename E::value_type>, E>
auto operator*(Scalar s, const MatrixExpr<E, typename E::value_type>& m);

// ---DEFINITION---

template<typename E, Arithmetic T>
ScalarMultExpr<E, T>::ScalarMultExpr(const E &expr, T alpha): expr_(expr), alpha_(alpha) {
}

template<typename E, Arithmetic T>
size_t ScalarMultExpr<E, T>::rows() const {
	return expr_.rows();
}

template<typename E, Arithmetic T>
size_t ScalarMultExpr<E, T>::cols() const {
	return expr_.cols();
}

template<typename E, Arithmetic T>
ScalarMultExpr<E, T>::value_type ScalarMultExpr<E, T>::operator()(size_t i, size_t j) const {
	std::cout << "ScalarMultExpr::operator() -> computing (" << i << ", " << j << ")\n";
	return expr_(i, j) * alpha_;
}

template<Arithmetic Scalar, typename E>
requires std::is_base_of_v<MatrixExpr<E, typename E::value_type>, E>
auto operator*(Scalar s, const MatrixExpr<E, typename E::value_type> &m) {
	return ScalarMultExpr<E, Scalar>( static_cast<const E&>(m), s );
}
