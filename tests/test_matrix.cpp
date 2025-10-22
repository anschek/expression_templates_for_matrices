//
// Created by anschek on 17.10.2025.
//

#include <fstream>

#include "matrices/matrix.h"
#include <gtest/gtest.h>

#include "matrices/diagonal_matrix.h"
#include "matrices/identity_matrix.h"
#include "matrices/zero_matrix.h"

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

TEST(MatrixTest, Constructor_ThrowException) {
	ASSERT_THROW(Matrix<int>({{1,2},{1,2,3}}), std::invalid_argument);
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
	m0.resize(m, n, false);
	ASSERT_EQ(m0.rows(), m);
	ASSERT_EQ(m0.cols(), n);
	for (size_t i = 0; i < m; ++i)
		for (size_t j = 0; j < n; ++j)
			ASSERT_EQ(m0(i,j), 0);

	Matrix m1 ({{1,2},{3,4}});
	Matrix m2 = m1;
	m2.resize(3, 3, true);
	ASSERT_EQ(m2.rows(), 3);
	ASSERT_EQ(m2.cols(), 3);
	for (size_t i = 0; i < 2; ++i)
		for (size_t j = 0; j < 2; ++j)
			ASSERT_EQ(m1(i,j), m2(i,j));
	std::cout << m1 << '\n';
	std::cout << m2 << '\n';

}

TEST(MatrixTest, Input_ObjectRead) {
	std::ifstream file("data/matrix_samples.txt");
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

TEST(MatrixTest, ZeroMatrix_CorrectObject) {
	ZeroMatrix O(5,6);
	ASSERT_EQ(O(0,0), 0);
	ASSERT_THROW(O(0,6), std::out_of_range);
	ASSERT_THROW(O(5,0), std::out_of_range);
	std::cout << O << '\n';

	Matrix OA = O;
	ASSERT_EQ(OA.rows(), 5);
	ASSERT_EQ(OA.cols(), 6);
}

TEST(MatrixTest, DiagonalMatrix_CorrectObject) {
	DiagonalMatrix A({5,6,7});
	ASSERT_EQ(A(1,1), 6);
	ASSERT_EQ(A(1,0), 0);
	ASSERT_THROW(A(1,3), std::out_of_range);
	std::cout << A << '\n';

	Matrix B = A;
	ASSERT_EQ(B.rows(), 3);
	ASSERT_EQ(B.cols(), 3);
}

TEST(MatrixTest, IdentityMatrix_CorrectObject) {
	IdentityMatrix I(3);
	ASSERT_EQ(I(0,0), 1);
	ASSERT_EQ(I(0,2), 0);
	ASSERT_THROW(I(0,3), std::out_of_range);
	std::cout << I << '\n';

	Matrix OI = I;
	ASSERT_EQ(OI.rows(), 3);
	ASSERT_EQ(OI.cols(), 3);
}
