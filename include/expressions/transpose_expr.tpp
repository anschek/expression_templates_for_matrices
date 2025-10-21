//
// Created by anschek on 21.10.2025.
//

template<typename E, typename T>
TransposeExpr<E, T>::TransposeExpr(const E &expr):expr_(expr) {
}

template<typename E, typename T>
size_t TransposeExpr<E, T>::rows() const {
	return expr_.cols();
}

template<typename E, typename T>
size_t TransposeExpr<E, T>::cols() const {
	return expr_.rows();
}

template<typename E, typename T>
T TransposeExpr<E, T>::operator()(size_t i, size_t j) const {
	std::cout << "TransposeExpr::operator() -> computing (" << i << ", " << j << ")\n";
	return expr_(j, i);
}