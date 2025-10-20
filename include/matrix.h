//
// Created by anschek on 17.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_MATRIX_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_MATRIX_H
#include <iosfwd>
#include <optional>
#include <vector>
#include "matrix_base.h"

template<typename T>
class Matrix: public MatrixExpr<Matrix<T>,T> {
public:
	// constructors
	Matrix(size_t rows, size_t cols);
	Matrix(size_t rows, size_t cols, const T &init_value);
	Matrix();
	Matrix(std::initializer_list<std::initializer_list<T>> data);
	template<typename E> Matrix(const MatrixExpr<E, T>& expr);

	// indexing and standard functions
	T &operator()(size_t i, size_t j);
	const T &operator()(size_t i, size_t j) const;
	void fill(const T &value);
	void resize(size_t new_rows, size_t new_cols, bool preserve = true);
	size_t rows() const;
	size_t cols() const;

private:
	size_t rows_, cols_;
	std::vector<T> data_;
};

template<typename T> std::ostream& operator<< (std::ostream& out, const Matrix<T>& obj);
template<typename T> std::istream& operator>>(std::istream& in, Matrix<T>& obj);
#include "matrix.tpp"
#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_MATRIX_H
