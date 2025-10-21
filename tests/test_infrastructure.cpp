//
// Created by anschek on 21.10.2025.
//

#include "matrix.h"
#include <gtest/gtest.h>

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
	Matrix A{{1,2},{3,4}};
	Matrix<double> B{{1.1,2},{3.3,4}};
	Matrix C = A + B;
	Matrix D = A - B;
	Matrix E = A * B;
	Matrix F = A * 2.5;
	ASSERT_TRUE((std::is_same_v<Matrix<double>, decltype(C)>));
	ASSERT_TRUE((std::is_same_v<Matrix<double>, decltype(D)>));
	ASSERT_TRUE((std::is_same_v<Matrix<double>, decltype(E)>));
	std::cout << C << '\n' << D << '\n' << E << '\n';
}