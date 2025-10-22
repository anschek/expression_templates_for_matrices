//
// Created by anschek on 22.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_CONCEPTS_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_CONCEPTS_H
#include <type_traits>
template<typename T>
concept Arithmetic = std::is_arithmetic_v<std::remove_cvref_t<T>>;

template<typename LHS, typename RHS>
using common_value_t = std::common_type_t<
	typename std::remove_cvref_t<LHS>::value_type,
	typename std::remove_cvref_t<RHS>::value_type
>;

template<typename E, typename S>
using common_value_scalar_t = std::common_type_t<
	typename std::remove_cvref_t<E>::value_type,
	std::remove_cvref_t<S>
>;
#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_CONCEPTS_H