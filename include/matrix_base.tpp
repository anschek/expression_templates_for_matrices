//
// Created by anschek on 20.10.2025.
//

template<typename Derived, typename T>
size_t MatrixExpr<Derived, T>::rows() const {
	return static_cast<const Derived &>(*this).rows();
}

template<typename Derived, typename T>
size_t MatrixExpr<Derived, T>::cols() const {
	return static_cast<const Derived &>(*this).cols();
}

template<typename Derived, typename T>
T MatrixExpr<Derived, T>::operator()(size_t i, size_t j) const {
	return static_cast<const Derived &>(*this)(i, j);
}

template<typename Derived, typename T>
template<typename Other>
AddExpr<Derived,Other,T> MatrixExpr<Derived, T>::operator+(const MatrixExpr<Other, T> &other) const {
	return AddExpr<Derived, Other, T>(static_cast<const Derived &>(*this),
									static_cast<const Other &>(other));
}

template<typename Derived, typename T>
template<typename Other>
SubExpr<Derived, Other, T> MatrixExpr<Derived, T>::operator-(const MatrixExpr<Other, T> &other) const {
	return SubExpr<Derived, Other, T>(static_cast<const Derived &>(*this),
								static_cast<const Other &>(other));
}

template<typename Derived, typename T>
ScalarMultExpr<Derived, T> MatrixExpr<Derived, T>::operator*(double alpha) const {
	return ScalarMultExpr<Derived, T>(static_cast<const Derived &>(*this), alpha);
}

template<typename Derived, typename T>
TransposeExpr<Derived, T> MatrixExpr<Derived, T>::transpose() const {
	return TransposeExpr<Derived, T>(static_cast<const Derived &>(*this));
}

template<typename Derived, typename T>
template<typename Other>
MultExpr<Derived, Other, T> MatrixExpr<Derived, T>::operator*(const MatrixExpr<Other, T> &other) const {
	return MultExpr<Derived, Other, T>(static_cast<const Derived &>(*this),
										static_cast<const Other &>(other));
}