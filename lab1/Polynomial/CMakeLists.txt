cmake_minimum_required(VERSION 3.15)
project(Polynomial CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(polynomial_domain
    src/Polynomial.cpp
)
target_include_directories(polynomial_domain PUBLIC include)

add_executable(polynomial src/main.cpp)
target_link_libraries(polynomial PRIVATE polynomial_domain)

enable_testing()

add_executable(polynomial_tests
    tests/test_polynomial.cpp
)
target_link_libraries(polynomial_tests PRIVATE polynomial_domain)
target_include_directories(polynomial_tests PRIVATE include tests)

add_test(NAME polynomial_tests COMMAND polynomial_tests)