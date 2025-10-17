//
// Created by anschek on 17.10.2025.
//

#include <ostream>
#include <istream>
#include <stdexcept>

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
	: rows_(rows), cols_(cols), data_(rows * cols) {
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T &init_value)
	: rows_(rows), cols_(cols), data_(rows * cols, init_value) {
}

template<typename T>
Matrix<T>::Matrix() : rows_(0), cols_(0) {
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> data){
	rows_ = data.size();
	cols_ = data.begin()->size();
	data_.reserve(rows_ * cols_);
	for (auto& row : data)
		data_.insert(data_.end(), row.begin(), row.end());
}

template<typename T>
T & Matrix<T>::operator()(size_t i, size_t j) {
	return data_.at(i * cols_ + j);
}

template<typename T>
const T& Matrix<T>::operator()(size_t i, size_t j) const {
	return data_.at(i * cols_ + j);
}

template<typename T>
void Matrix<T>::fill(const T &value) {
	data_.assign(rows_ * cols_, value);
}

template<typename T>
void Matrix<T>::resize(size_t new_rows, size_t new_cols) {
	rows_ = new_rows;
	cols_ = new_cols;
	data_.assign(new_rows * new_cols, 0);
}

template<typename T>
size_t Matrix<T>::rows() const {
	return rows_;
}

template<typename T>
size_t Matrix<T>::cols() const {
	return cols_;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &other) const {
	if (rows_ != other.rows_ || cols_ != other.cols_) {
		throw std::invalid_argument("Matrix dimensions do not match");
	}
	Matrix result(rows_, cols_);
	for (size_t i = 0; i < rows_; ++i)
		for (size_t j = 0; j < cols_; ++j)
			result(i, j) = (*this)(i, j) + other(i, j);
	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-() const {
		Matrix result(rows_, cols_);
		for (size_t i = 0; i < rows_; ++i)
			for (size_t j = 0; j < cols_; ++j)
				result(i, j) = -(*this)(i, j);
		return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix &other) const {
	return *this + (-other);
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &obj) {
	for (size_t i = 0; i < obj.rows(); ++i) {
		for (size_t j = 0; j < obj.cols(); ++j) {
			out << obj(i, j) << ' ';
		}
		out << '\n';
	}
	return out;
}

template<typename T>
std::istream & operator>>(std::istream &in, Matrix<T> &obj) {
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
