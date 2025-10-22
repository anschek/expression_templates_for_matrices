//
// Created by anschek on 21.10.2025.
//

#include "matrices/matrix.h"
#include <gtest/gtest.h>
#include <iostream>
#include "matrices/identity_matrix.h"

template<Arithmetic T>
struct OnlyArithmetic { using type = T; };

template<typename T>
constexpr bool is_instantiable_v = requires { typename OnlyArithmetic<T>::type; };

TEST(InfrastructureTest, Concept_Arithmetic) {
	ASSERT_TRUE(is_instantiable_v<int>);
	ASSERT_TRUE(is_instantiable_v<double>);
	ASSERT_FALSE(is_instantiable_v<std::string>);
	ASSERT_FALSE(is_instantiable_v<std::vector<int>>);
}

TEST(InfrastructureTest, CommonType_CastExpr) {
	Matrix<int> A{{1,2},{3,4}};
	Matrix<double> B{{1.1,2},{3.3,4}};
	Matrix C = A + B;
	Matrix D = A - B;
	Matrix E = A * B;
	Matrix F = 7.5 * A * 3;
	ASSERT_TRUE((std::is_same_v<Matrix<double>, decltype(C)>));
	ASSERT_TRUE((std::is_same_v<Matrix<double>, decltype(D)>));
	ASSERT_TRUE((std::is_same_v<Matrix<double>, decltype(E)>));
	ASSERT_TRUE((std::is_same_v<Matrix<double>, decltype(F)>));
	std::cout << C << '\n' << D << '\n' << E << '\n' << F << '\n';
}

TEST(InfrastructureTest, CommonType_SpecialTypes) {
	IdentityMatrix I(3);
	Matrix A (3,3,5.2);
	Matrix B = A + I;
	ASSERT_TRUE((std::is_same_v<Matrix<double>, decltype(B)>));
	ASSERT_EQ(B.rows(), 3);
	ASSERT_EQ(B.cols(), 3);
	ASSERT_EQ(B(0,0), 6.2);
}