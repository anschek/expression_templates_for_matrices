//
// Created by anschek on 21.10.2025.
//

#include <sstream>

template<typename LHS, typename RHS, typename T>
MultExpr<LHS, RHS, T>::MultExpr(const LHS &lhs, const RHS &rhs) : lhs_(lhs), rhs_(rhs), n_(lhs.cols()) {
	if (n_ != rhs.rows()) {
		std::stringstream ss;
		ss << "Matrix dimensions do not match: left cols " << n_ << " != right rows " << rhs.rows();
		throw std::invalid_argument(ss.str());
	}
}

template<typename LHS, typename RHS, typename T>
size_t MultExpr<LHS, RHS, T>::rows() const {
	return lhs_.rows();
}

template<typename LHS, typename RHS, typename T>
size_t MultExpr<LHS, RHS, T>::cols() const {
	return rhs_.cols();
}

template<typename LHS, typename RHS, typename T>
T MultExpr<LHS, RHS, T>::operator()(size_t i, size_t j) const {
	std::cout << "MultExpr::operator() -> computing (" << i << ", " << j << ")\n";
	T sum{};
	for (size_t k = 0; k < n_; ++k)
		sum += lhs_(i, k) * rhs_(k, j);
	return sum;
}
