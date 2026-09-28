#pragma once
#include <iostream>

enum class Cell {
    Empty,
    X,
    O
};

class Board {
public:
    explicit Board(int size);
    Board(const Board& other);
    Board& operator=(const Board& other);
    ~Board();

    int Size() const;
    Cell Get(int row, int col) const;
    void Set(int row, int col, Cell value);
    bool CanPlace(int row, int col) const;
    bool HasWinner(Cell player) const;
    bool IsFull() const;

    bool operator==(const Board& other) const;
    bool operator!=(const Board& other) const;

    Cell* operator[](int row);
    const Cell* operator[](int row) const;

private:
    int size_;
    Cell* cells_;
};

std::ostream& operator<<(std::ostream& os, const Board& board);
std::istream& operator>>(std::istream& is, Board& board);

