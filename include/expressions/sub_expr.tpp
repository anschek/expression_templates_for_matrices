//
// Created by anschek on 20.10.2025.
//

template<typename LHS, typename RHS>
SubExpr<LHS, RHS>::SubExpr(const LHS &lhs, const RHS &rhs): lhs_(lhs), rhs_(rhs) {
	if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())
		throw std::invalid_argument("Matrix dimensions do not match");
}

template<typename LHS, typename RHS>
size_t SubExpr<LHS, RHS>::rows() const {
	return lhs_.rows();
}

template<typename LHS, typename RHS>
size_t SubExpr<LHS, RHS>::cols() const {
	return lhs_.cols();
}

template<typename LHS, typename RHS>
SubExpr<LHS, RHS>::value_type SubExpr<LHS, RHS>::operator()(size_t i, size_t j) const {
	std::cout << "SubExpr::operator() -> computing (" << i << ", " << j << ")\n";
	return lhs_(i, j) - rhs_(i, j);
}
