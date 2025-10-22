//
// Created by anschek on 22.10.2025.
//

#ifndef EXPRESSION_TEMPLATES_FOR_MATRICES_ELEMENTWISE_OPS_H
#define EXPRESSION_TEMPLATES_FOR_MATRICES_ELEMENTWISE_OPS_H
// operations that execute sequentially
struct AddOp {
	inline static const char* name = "AddOp";
	template<typename A, typename B>
	constexpr auto operator()(A&& a, B&& b) const -> decltype(a + b) { return a + b; }
};
struct SubOp {
	inline static const char* name = "SubOp";
	template<typename A, typename B>
	constexpr auto operator()(A&& a, B&& b) const -> decltype(a - b) { return a - b; }
};
#endif //EXPRESSION_TEMPLATES_FOR_MATRICES_ELEMENTWISE_OPS_H