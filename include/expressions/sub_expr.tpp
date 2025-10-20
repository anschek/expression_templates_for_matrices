//
// Created by anschek on 20.10.2025.
//

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
