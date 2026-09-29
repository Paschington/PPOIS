cmake_minimum_required(VERSION 3.15)
project(Tictactoe CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(tictactoe_domain
    src/TicTacToe.cpp
)
target_include_directories(tictactoe_domain PUBLIC include)

add_executable(tictactoe src/main.cpp)
target_link_libraries(tictactoe PRIVATE tictactoe_domain)

enable_testing()

add_executable(tictactoe_tests
    tests/test_tic_tac_toe.cpp
)
target_link_libraries(tictactoe_tests PRIVATE tictactoe_domain)
target_include_directories(tictactoe_tests PRIVATE include tests)

add_test(NAME tictactoe_tests COMMAND tictactoe_tests)