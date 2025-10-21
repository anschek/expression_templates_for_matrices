//
// Created by anschek on 20.10.2025.
//

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
T ScalarMultExpr<E, T>::operator()(size_t i, size_t j) const {
	std::cout << "ScalarMultExpr::operator() -> computing (" << i << ", " << j << ")\n";
	return expr_(i, j) * alpha_;
}
