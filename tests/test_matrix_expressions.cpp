//
// Created by anschek on 20.10.2025.
//

#include "matrices/matrix.h"
#include <gtest/gtest.h>

#include "matrices/diagonal_matrix.h"
#include "matrices/identity_matrix.h"
#include "matrices/zero_matrix.h"

TEST(MatrixExprTest, AddExpr_Structure) {
	Matrix A{{1, 2}, {3, 4}};
	Matrix B{{5, 6}, {7, 8}};

	auto expr = A + B; // AddExpr
	ASSERT_EQ(expr.rows(), 2);
	ASSERT_EQ(expr.cols(), 2);
	ASSERT_EQ(expr(0, 1), 8);
	ASSERT_EQ(expr(1, 1), 12);
}

TEST(MatrixExprTest, AddExpr_Evaluation) {
	Matrix A{{1, 2}, {3, 4}};
	Matrix B{{10, 20}, {30, 40}};
	Matrix C = A + B;

	ASSERT_EQ(C(0, 0), 11);
	ASSERT_EQ(C(1, 1), 44);
}

TEST(MatrixExprTest, AddExpr_Chained) {
	Matrix A{{1, 2}, {3, 4}};
	Matrix B{{5, 6}, {7, 8}};
	Matrix C{{10, 20}, {30, 40}};

	Matrix R = A + B + C;
	ASSERT_EQ(R(0, 0), 16);
	ASSERT_EQ(R(0, 1), 28);
}

TEST(MatrixExprTest, SubExpr_Evaluation) {
	Matrix A{{1, 2}, {3, 4}};
	Matrix B{{10, 20}, {30, 40}};
	Matrix C = B - A;

	ASSERT_EQ(C(0, 0), 9);
	ASSERT_EQ(C(1, 1), 36);
}

TEST(MatrixExprTest, AddSubExpr_Chained) {
	Matrix A{{1, 2}, {3, 4}};
	Matrix B{{5, 6}, {7, 8}};
	Matrix C{{10, 20}, {30, 40}};

	Matrix R = C - ( A + B );
	ASSERT_EQ(R(0, 0), 4);
	ASSERT_EQ(R(0, 1), 12);
}

TEST(MatrixExprTest,AddSubExpr_ThrowException) {
	Matrix A{{1, 2}, {3, 4}};
	Matrix B{{5, 6}, {7, 8}, {10, 3}};

	ASSERT_THROW(Matrix(A+B), std::invalid_argument);
	ASSERT_THROW(Matrix(A-B), std::invalid_argument);
}

TEST(MatrixExprTest, ScalarMultExpr_Evaluation) {
	Matrix A{{1, 2}, {3, 4}};
	int alpha1 = 2;
	Matrix B(A*alpha1);

	ASSERT_EQ(B(0, 0), 2);
	ASSERT_EQ(B(1, 1), 8);

	Matrix<double> C{{1, 2}, {3, 4}};
	double alpha2 = 2.2;
	Matrix D = C*alpha2;

	ASSERT_EQ(D(0, 0), 2.2);
	ASSERT_EQ(D(1, 1), 8.8);
}

TEST(MatrixExprTest, TranspocseExpr_Evaluation) {
	Matrix A{{1, 2}, {3, 4}, {5,6}};
	Matrix B{{1,3,5}, {2,4,6}};
	A = A.transpose();
	ASSERT_EQ(A.rows(), B.rows());
	ASSERT_EQ(A.cols(), B.cols());

	for (int i = 0; i < B.rows(); ++i)
		for (int j = 0; j < B.cols(); ++j)
			ASSERT_EQ(A(i,j), B(i,j));
}

TEST(MatrixExprTest, MultExpr_Evaluation) {
	Matrix A{{1,2,3}, {-7,-2,-5}};
	Matrix B{{1,4,0,2},{2,-3,7,2},{2,-2,4,1}};
	Matrix C{{11, -8, 26, 9}, {-21, -12, -34, -23}};
	Matrix D = A * B;

	for (int i = 0; i < A.rows(); ++i)
		for (int j = 0; j < B.cols(); ++j)
			ASSERT_EQ(D(i,j), C(i,j));
}

TEST(MatrixExprTest, SpecialTypes_Chained) {
	ZeroMatrix A{3,3};
	DiagonalMatrix B{3,4,5};
	IdentityMatrix C{3};

	Matrix D = A + B + C;
	ASSERT_EQ(D(0, 0), 4);
	ASSERT_EQ(D(2, 2), 6);
	ASSERT_EQ(D(0, 2), 0);
}