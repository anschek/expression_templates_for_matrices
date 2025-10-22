//
// Created by anschek on 22.10.2025.
//

#include "matrices/matrix.h"
#include "analysis/norms.h"
#include <gtest/gtest.h>

#include "analysis/determinant.h"
#include "analysis/lu_decompose.h"

TEST(AnalysisTest, Norm1_CorrectResult) {
	Matrix A {{1,-2},{3,4}};
	auto norm = analysis::norm1(A);
	ASSERT_EQ(norm,6);
}

TEST(AnalysisTest, NormInf_CorrectResult) {
	Matrix A {{1,-2},{3,4}};
	auto norm = analysis::normInf(A);
	ASSERT_EQ(norm,7);
}

TEST(AnalysisTest, NormFrobenius_CorrectResult) {
	Matrix A {{1,-2},{3,4}};
	auto norm = analysis::normFrobenius(A);
	ASSERT_NEAR(norm,5.48, 1e-2);
}

TEST(AnalysisTest, LuDecompose_CorrectDecomposition) {
	Matrix<double> A{{2, 1, 1},
					 {4, 3, 3},
					 {8, 7, 9}};
	Matrix<double> A_copy = A;
	ASSERT_TRUE(analysis::lu_decompose(A_copy));

	auto L = analysis::extract_L(A_copy);
	auto U =analysis:: extract_U(A_copy);
	Matrix reconstructed =L* U;
	EXPECT_TRUE(reconstructed == A);
}

TEST(AnalysisTest, LuDecompose_ThrowException) {
	Matrix<double> A(2, 3);
	ASSERT_THROW(analysis::lu_decompose(A), std::invalid_argument);
}

TEST(AnalysisTest, LuDecompose_ContainsZerosOnMainDiagonal) {
	Matrix<double> A{{1, 2, 3},
					 {2, 4, 6}, // = 2 * первая строка
					 {0, 1, 1}};
	ASSERT_FALSE(analysis::lu_decompose(A));
}

TEST(AnalysisTest, Dererminant_CorrectResult) {
	Matrix<double> A{{2, 1, 1},
					 {4, 3, 3},
					 {8, 7, 9}};

	double det = analysis::determinant_lu(A);
	ASSERT_NEAR(det, 4.0, 1e-2);
}

TEST(AnalysisTest, Dererminant_ThrowException) {
	Matrix<double> A(3, 2);
	ASSERT_THROW(analysis::determinant_lu(A), std::invalid_argument);
}

TEST(AnalysisTest, Dererminant_ContainsZerosOnMainDiagonal) {
	Matrix<double> A{{1, 2, 3},
					 {2, 4, 6},
					 {0, 1, 1}};
	double det = analysis::determinant_lu(A);
	EXPECT_NEAR(det, 0.0, 1e-2);
}