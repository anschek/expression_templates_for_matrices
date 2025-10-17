//
// Created by anschek on 17.10.2025.
//

#include <fstream>

#include "matrix.h"
#include <gtest/gtest.h>

TEST(MatrixTest, Constructor_ObjectCreated) {
	Matrix<int> m0{};
	ASSERT_EQ(m0.rows(), 0);
	ASSERT_EQ(m0.cols(), 0);

	Matrix m1(2, 4, 3.2);
	ASSERT_EQ(m1.rows(), 2);
	ASSERT_EQ(m1.cols(), 4);
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 4; ++j)
			ASSERT_EQ(m1(i,j), 3.2);
	std::cout << m1 << '\n';

	std::initializer_list<std::initializer_list<size_t> > init{{1, 2}, {3, 4}, {5, 6}};
	Matrix m2(init);
	ASSERT_EQ(m2.rows(), 3);
	ASSERT_EQ(m2.cols(), 2);
	size_t i = 0, j = 0;
	for (const auto &inner_list: init) {
		for (size_t elem: inner_list) {
			ASSERT_EQ(m2(i,j), elem);
			++j;
		}
		j = 0;
		++i;
	}
	std::cout << m2 << '\n';
}

TEST(MatrixTest, Fill_Filled) {
	size_t m=3, n=4;
	Matrix<int> m0(m, n);
	m0.fill(-10);
	for (size_t i = 0; i < m; ++i)
		for (size_t j = 0; j < n; ++j)
			ASSERT_EQ(m0(i,j), -10);
}

TEST(MatrixTest, Resize_ObjectResizedAndCleared) {
	size_t m=2, n=5;
	Matrix<int> m0;
	m0.resize(m, n);
	ASSERT_EQ(m0.rows(), m);
	ASSERT_EQ(m0.cols(), n);
	for (size_t i = 0; i < m; ++i)
		for (size_t j = 0; j < n; ++j)
			ASSERT_EQ(m0(i,j), 0);
}

TEST(MatrixTest, Addition_ReturnOfSumObject) {
	size_t m=2, n=5;
	Matrix m0(2,5,7);
	Matrix m1(2,5,3);

	Matrix m2 = m0 + m1;
	ASSERT_EQ(m2.rows(), m);
	ASSERT_EQ(m2.cols(), n);
	for (size_t i = 0; i < m; ++i)
		for (size_t j = 0; j < n; ++j)
			ASSERT_EQ(m2(i,j), 10);
}

TEST(MatrixTest, Subtraction_ReturnDififferenceObject) {
	size_t m=2, n=5;
	Matrix m0(2,5,3.5);
	m0 = -m0;
	ASSERT_EQ(m0.cols(), n);
	for (size_t i = 0; i < m; ++i)
		for (size_t j = 0; j < n; ++j)
			ASSERT_EQ(m0(i,j), -3.5);

	const Matrix m1(2,5,8.0);

	Matrix<double> m2 = m1 - m0;
	ASSERT_EQ(m2.rows(), m);
	ASSERT_EQ(m2.cols(), n);
	for (size_t i = 0; i < m; ++i)
		for (size_t j = 0; j < n; ++j)
			ASSERT_EQ(m2(i,j), 11.5);
}

TEST(MatrixTest, Input_ObjectRead) {
	std::ifstream file(R"(..\data\matrix_samples.txt)");
	Matrix<int> m;
	if (file.is_open()) {
		try {
			while (file >> m) {
				std::cout << m << '\n';
			}
		} catch (...) {
			FAIL();
		}
	} else {
		FAIL();
	}
}
