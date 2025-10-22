//
// Created by anschek on 17.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_MATRIX_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_MATRIX_H
#include <iosfwd>
#include <vector>
#include "matrix_base.h"

template<Arithmetic T>
class Matrix: public MatrixExpr<Matrix<T>,T> {
public:
	using value_type = T;
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

template<Arithmetic T> std::ostream& operator<< (std::ostream& out, const Matrix<T>& obj);
template<Arithmetic T> std::istream& operator>>(std::istream& in, Matrix<T>& obj);

// ---DEFINITION---

template<Arithmetic T>
Matrix<T>::Matrix(size_t rows, size_t cols)
	: rows_(rows), cols_(cols), data_(rows * cols) {
}

template<Arithmetic T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T &init_value)
	: rows_(rows), cols_(cols), data_(rows * cols, init_value) {
}

template<Arithmetic T>
Matrix<T>::Matrix() : rows_(0), cols_(0) {
}

template<Arithmetic T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T> > data) {
	rows_ = data.size();
	cols_ = data.begin()->size();
	data_.reserve(rows_ * cols_);
	for (const auto &row: data) {
		if (row.size() != cols_)
			throw std::invalid_argument("All rows must have the same number of elements");
		data_.insert(data_.end(), row.begin(), row.end());
	}
}

template<Arithmetic T>
template<typename E>
Matrix<T>::Matrix(const MatrixExpr<E, T> &expr)
	: rows_(expr.rows()), cols_(expr.cols()), data_(rows_ * cols_) {
	std::cout << "Matrix::construct from expression (" << rows_ << "x" << cols_ << ")\n";
	for (size_t i = 0; i < rows_; ++i)
		for (size_t j = 0; j < cols_; ++j)
			(*this)(i, j) = expr(i, j);
}

template<Arithmetic T>
T &Matrix<T>::operator()(size_t i, size_t j) {
	return data_.at(i * cols_ + j);
}

template<Arithmetic T>
const T &Matrix<T>::operator()(size_t i, size_t j) const {
	return data_.at(i * cols_ + j);
}

template<Arithmetic T>
void Matrix<T>::fill(const T &value) {
	data_.assign(rows_ * cols_, value);
}

template<Arithmetic T>
void Matrix<T>::resize(size_t new_rows, size_t new_cols, bool preserve) {
	if (!preserve) {
		rows_ = new_rows;
		cols_ = new_cols;
		data_.assign(new_rows * new_cols, T{});
		return;
	}
	std::vector<T> new_data(new_rows * new_cols, T{});
	size_t min_rows = std::min(rows_, new_rows);
	size_t min_cols = std::min(cols_, new_cols);

	for (size_t i = 0; i < min_rows; ++i)
		for (size_t j = 0; j < min_cols; ++j)
			new_data[i * new_cols + j] = std::move((*this)(i, j));

	data_.swap(new_data);
	rows_ = new_rows;
	cols_ = new_cols;
}

template<Arithmetic T>
size_t Matrix<T>::rows() const {
	return rows_;
}

template<Arithmetic T>
size_t Matrix<T>::cols() const {
	return cols_;
}

template<Arithmetic T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &obj) {
	for (size_t i = 0; i < obj.rows(); ++i) {
		for (size_t j = 0; j < obj.cols(); ++j) {
			out << obj(i, j) << ' ';
		}
		out << '\n';
	}
	return out;
}

template<Arithmetic T>
std::istream &operator>>(std::istream &in, Matrix<T> &obj) {
	size_t rows, cols;
	if (!(in >> rows >> cols)) {
		in.setstate(std::ios::failbit);
		return in;
	}

	obj.resize(rows, cols);
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < cols; ++j) {
			if (!(in >> obj(i, j))) {
				in.setstate(std::ios::failbit);
				return in;
			}
		}
	}
	return in;
}

#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_MATRIX_H
