//
// Created by anschek on 21.10.2025.
//

template<typename Derived, Arithmetic T> class MatrixExpr;

template<typename E, Arithmetic T>
class TransposeExpr : public MatrixExpr<TransposeExpr<E, T>, T> {
public:
	using value_type = T;
	TransposeExpr(const E &expr);
	size_t rows() const;
	size_t cols() const;
	T operator()(size_t i, size_t j) const;

private:
	const E &expr_;
};

// ---DEFINITION---

template<typename E, Arithmetic T>
TransposeExpr<E, T>::TransposeExpr(const E &expr):expr_(expr) {
}

template<typename E, Arithmetic T>
size_t TransposeExpr<E, T>::rows() const {
	return expr_.cols();
}

template<typename E, Arithmetic T>
size_t TransposeExpr<E, T>::cols() const {
	return expr_.rows();
}

template<typename E, Arithmetic T>
T TransposeExpr<E, T>::operator()(size_t i, size_t j) const {
	std::cout << "TransposeExpr::operator() -> computing (" << i << ", " << j << ")\n";
	return expr_(j, i);
}