#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "TicTacToe.h"

// --- Создание ---

TEST_CASE("Board size is stored", "[Board]") {
    Board b(3);
    REQUIRE(b.Size() == 3);
}

TEST_CASE("Board with size 5 is stored", "[Board]") {
    Board b(5);
    REQUIRE(b.Size() == 5);
}

TEST_CASE("Board is initially empty", "[Board]") {
    Board b(3);
    REQUIRE(b.Get(0, 0) == Cell::Empty);
    REQUIRE(b.Get(2, 2) == Cell::Empty);
    REQUIRE(!b.IsFull());
}

// --- Get / Set ---

TEST_CASE("Board set and get work", "[Board]") {
    Board b(3);
    b.Set(1, 1, Cell::X);
    REQUIRE(b.Get(1, 1) == Cell::X);
}

TEST_CASE("Board set O and get O", "[Board]") {
    Board b(3);
    b.Set(0, 2, Cell::O);
    REQUIRE(b.Get(0, 2) == Cell::O);
}

// --- CanPlace ---

TEST_CASE("Board can place on empty cell", "[Board]") {
    Board b(3);
    REQUIRE(b.CanPlace(0, 0));
    REQUIRE(b.CanPlace(2, 2));
}

TEST_CASE("Board cannot place out of bounds", "[Board]") {
    Board b(3);
    REQUIRE(!b.CanPlace(-1, 0));
    REQUIRE(!b.CanPlace(0, 100));
    REQUIRE(!b.CanPlace(3, 3));
}

TEST_CASE("Board cannot place on occupied cell", "[Board]") {
    Board b(3);
    b.Set(0, 0, Cell::X);
    REQUIRE(!b.CanPlace(0, 0));
}

// --- HasWinner ---

TEST_CASE("Board detects winner in row", "[Board]") {
    Board b(3);
    b.Set(0, 0, Cell::X);
    b.Set(0, 1, Cell::X);
    b.Set(0, 2, Cell::X);
    REQUIRE(b.HasWinner(Cell::X));
    REQUIRE(!b.HasWinner(Cell::O));
}

TEST_CASE("Board detects winner in column", "[Board]") {
    Board b(3);
    b.Set(0, 1, Cell::O);
    b.Set(1, 1, Cell::O);
    b.Set(2, 1, Cell::O);
    REQUIRE(b.HasWinner(Cell::O));
}

TEST_CASE("Board detects winner in main diagonal", "[Board]") {
    Board b(3);
    b.Set(0, 0, Cell::X);
    b.Set(1, 1, Cell::X);
    b.Set(2, 2, Cell::X);
    REQUIRE(b.HasWinner(Cell::X));
}

TEST_CASE("Board detects winner in anti diagonal", "[Board]") {
    Board b(3);
    b.Set(0, 2, Cell::O);
    b.Set(1, 1, Cell::O);
    b.Set(2, 0, Cell::O);
    REQUIRE(b.HasWinner(Cell::O));
}

TEST_CASE("Board detects no winner", "[Board]") {
    Board b(3);
    b.Set(0, 0, Cell::X);
    b.Set(0, 1, Cell::O);
    REQUIRE(!b.HasWinner(Cell::X));
    REQUIRE(!b.HasWinner(Cell::O));
}

// --- IsFull ---

TEST_CASE("Board is full when all cells filled", "[Board]") {
    Board b(3);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            b.Set(i, j, Cell::X);
    REQUIRE(b.IsFull());
}

TEST_CASE("Board is not full when at least one cell is empty", "[Board]") {
    Board b(3);
    b.Set(0, 0, Cell::X);
    REQUIRE(!b.IsFull());
}

// --- Копирование ---

TEST_CASE("Board copy constructor is independent", "[Board]") {
    Board a(3);
    a.Set(0, 0, Cell::X);
    Board b(a);
    b.Set(1, 1, Cell::O);
    REQUIRE(a != b);
    REQUIRE(a.Get(0, 0) == Cell::X);
    REQUIRE(b.Get(1, 1) == Cell::O);
}

TEST_CASE("Board assignment works", "[Board]") {
    Board a(3);
    Board b(5);
    a = b;
    REQUIRE(a.Size() == 5);
}

TEST_CASE("Board self-assignment is safe", "[Board]") {
    Board a(3);
    a.Set(0, 0, Cell::X);
    a = a;
    REQUIRE(a.Get(0, 0) == Cell::X);
}

// --- Равенство ---

TEST_CASE("Boards are equal when identical", "[Board]") {
    Board a(3);
    Board b(3);
    REQUIRE(a == b);
}

TEST_CASE("Boards are not equal when different", "[Board]") {
    Board a(3);
    Board b(3);
    a.Set(0, 0, Cell::X);
    REQUIRE(a != b);
}

// --- operator[] ---

TEST_CASE("Board operator[] returns row pointer", "[Board]") {
    Board b(3);
    b.Set(1, 1, Cell::X);
    Cell* row = b[1];
    REQUIRE(row[1] == Cell::X);
}