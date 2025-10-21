//
// Created by anschek on 20.10.2025.
//

template<typename Derived, Arithmetic T>
size_t MatrixExpr<Derived, T>::rows() const {
	return static_cast<const Derived &>(*this).rows();
}

template<typename Derived, Arithmetic T>
size_t MatrixExpr<Derived, T>::cols() const {
	return static_cast<const Derived &>(*this).cols();
}

template<typename Derived, Arithmetic T>
T MatrixExpr<Derived, T>::operator()(size_t i, size_t j) const {
	return static_cast<const Derived &>(*this)(i, j);
}

template<typename Derived, Arithmetic T>
template<typename OtherDerived, Arithmetic OtherT>
AddExpr<Derived,OtherDerived> MatrixExpr<Derived, T>::operator+(const MatrixExpr<OtherDerived, OtherT> &other) const {
	return AddExpr<Derived, OtherDerived>(static_cast<const Derived &>(*this),
								static_cast<const OtherDerived &>(other));
}

template<typename Derived, Arithmetic T>
template<typename OtherDerived, Arithmetic OtherT>
SubExpr<Derived, OtherDerived> MatrixExpr<Derived, T>::operator-(const MatrixExpr<OtherDerived, OtherT> &other) const {
	return SubExpr<Derived, OtherDerived>(static_cast<const Derived &>(*this),
								static_cast<const OtherDerived &>(other));
}

template<typename Derived, Arithmetic T>
ScalarMultExpr<Derived, T> MatrixExpr<Derived, T>::operator*(double alpha) const {
	return ScalarMultExpr<Derived, T>(static_cast<const Derived &>(*this), alpha);
}

template<typename Derived, Arithmetic T>
TransposeExpr<Derived, T> MatrixExpr<Derived, T>::transpose() const {
	return TransposeExpr<Derived, T>(static_cast<const Derived &>(*this));
}

template<typename Derived, Arithmetic T>
template<typename OtherDerived, Arithmetic OtherT>
MultExpr<Derived, OtherDerived> MatrixExpr<Derived, T>::operator*(const MatrixExpr<OtherDerived, OtherT> &other) const {
	return MultExpr<Derived, OtherDerived>(static_cast<const Derived &>(*this),
										static_cast<const OtherDerived &>(other));
}