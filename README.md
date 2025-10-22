# Expression Templates for Matrices

**A high-performance C++20 linear algebra project with lazy evaluation, CRTP, specialized matrix types, calculation of norms and analysis operations**

## Overview

This project implements a **lazy-evaluated expression template system** for dense and structured matrices in C++20. Instead of computing intermediate results immediately, the library builds expression trees that are evaluated only upon assignment—eliminating unnecessary temporaries and enabling aggressive compiler optimizations.

The design leverages modern C++ features:
- **Expression templates** for zero-overhead abstractions
- **CRTP (Curiously Recurring Template Pattern)** for static polymorphism
- **C++20 Concepts** for clean, constrained interfaces
- **`std::common_type`** for automatic type promotion in mixed-type expressions
- **Specialized matrix types**: zero, identity, and diagonal matrices with optimized storage and operations

All core functionality is covered by **30+ rigorous GoogleTest unit tests**, automatically validated via GitHub Actions.

## Key Features

### 1. **Lazy Expression Evaluation**
Matrix expressions like `A + B * C` or `alpha * (M.transpose() + I)` are **not evaluated until assigned** to a concrete matrix. This avoids intermediate allocations and enables:
- **Loop fusion**: `C = A + B` → single pass over memory
- **Dead code elimination**: unused subexpressions are never computed
- **Optimal evaluation order**: compiler reorders operations for efficiency

### 2. **Specialized Matrix Types**
- `ZeroMatrix`: O(1) storage, implicit zeros
- `IdentityMatrix`: O(1) storage, implicit identity
- `DiagonalMatrix`: O(n) storage, implicit off-diagonals = 0  
*All seamlessly interoperate with dense `Matrix<T>` via expression templates.*

### 3. **Type Safety & Interoperability**
- **Arithmetic concept**: Only numeric types allowed (`int`, `float`, `double`, etc.)
- **Automatic type promotion**: `Matrix<int> + Matrix<double> → Matrix<double>`
- **Dimension checks**: Compile-time and runtime validation

### 4. **Linear Algebra Utilities**
- **Matrix operations**: `+`, `-`, `*` (scalar/matrix), `.transpose()`
- **Norms**: 1-norm, ∞-norm, Frobenius norm
- **Decomposition**: LU decomposition 
- **Determinant**: Computed via LU decomposition

## Quality Assurance

- **30+ unit tests** covering:
  - Core matrix operations and constructors
  - Lazy expression evaluation correctness
  - Type promotion and concept constraints
  - Specialized matrix interoperability
  - Numerical analysis (norms, LU, determinant)
- **Continuous Integration**: Tests run on every push via GitHub Actions
- **Dockerized builds**: Reproducible environment for all developers


## Quick Start

### Run with Docker
```bash
# Clone the repo
git clone https://github.com/anschek/expression_templates_for_matrices.git
cd expression_templates_for_matrices

# Build and run tests in isolated environment
docker build -t matrix-tests .
docker run --rm matrix-tests
```

## Usage Examples

### Basic Operations
```cpp
Matrix A{{1, 2}, {3, 4}};
Matrix B{{5, 6}, {7, 8}};
Matrix C = A + B; // Lazy: no temp until assignment
Matrix D = 2.0 * A - B; // Mixed scalar/matrix ops
```

### Specialized Matrices
```cpp
ZeroMatrix Z(3, 3);
IdentityMatrix I(3);
DiagonalMatrix D({2, 3, 4});

Matrix M = Z + I + D; // Efficient: only diagonal stored
// M = {{3, 0, 0},
//      {0, 4, 0},
//      {0, 0, 5}}
```

### Type Promotion
```cpp
Matrix<int> A{{1, 2}};
Matrix<double> B{{1.5, 2.5}};
auto C = A + B; // is ElementwiseExpr<Matrix<int>, Matrix<double>, AddOp>
Matrix D = A + B; // is Matrix<double>
```

### Numerical Analysis
```cpp
	Matrix A{{2, 1}, {-4, 3}};
	auto norm1 = analysis::norm1(A); // 6
	auto normF = analysis::normFrobenius(A); // ≈5.48

	Matrix<double> B{
      {2, 1, 1},
      {4, 3, 3},
      {8, 7, 9}
	};
	Matrix<double> B_copy = B;
	if (analysis::lu_decompose(B_copy)) {
		auto L = analysis::extract_L(B_copy);
		auto U = analysis::extract_U(B_copy);
		Matrix reconstructed = L * U;
		assert(reconstructed == B);
	}

	double det = analysis::determinant_lu(B); // 4
```

## Description of commits
| Name     | Description								|
| -------- | -----------------------------------------------------------------------|
| build    | changes related to the build system or external dependencies		|
| chore    | updating docs, refact code comments, changes that don't affect functionality|
| docs     | update documentation					 |
| feat     | adding new functionality							 |
| style    | style changes to improve code readability or aesthetics			 |
| fix      | error correction								 |
| perf     | changes to improve the program						 |
| refactor | code edits without changing errors or functionality			 |
| revert   | rollback to previous versions						 |
| test     | adding Tests								 |
| ci       | setting up or changing CI/CD						 |

