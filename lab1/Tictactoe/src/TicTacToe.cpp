#include "Tictactoe.h"

Board::Board(int size) {
    size_ = size;
    cells_ = new Cell[size_ * size_];
    for (int i = 0; i < size_ * size_; i++) {
        cells_[i] = Cell::Empty;
    }
}

Board::Board(const Board& other) {
    size_ = other.size_;
    cells_ = new Cell[size_ * size_];
    for (int i = 0; i < size_ * size_; i++) {
        cells_[i] = other.cells_[i];
    }
}

Board& Board::operator=(const Board& other) {
    if (this == &other) {
        return *this;
    }

    delete[] cells_;

    size_ = other.size_;
    cells_ = new Cell[size_ * size_];
    for (int i = 0; i < size_ * size_; i++) {
        cells_[i] = other.cells_[i];
    }

    return *this;
}

Board::~Board() {
    delete[] cells_;
}

int Board::Size() const {
    return size_;
}

Cell Board::Get(int row, int col) const {
    return cells_[row * size_ + col];
}

void Board::Set(int row, int col, Cell value) {
    cells_[row * size_ + col] = value;
}

bool Board::CanPlace(int row, int col) const {
    if (row < 0 || row >= size_ || col < 0 || col >= size_) {
        return false;
    }
    return Get(row, col) == Cell::Empty;
}

bool Board::HasWinner(Cell player) const {
    for (int i = 0; i < size_; i++) {
        bool rowWin = true;
        bool colWin = true;
        for (int j = 0; j < size_; j++) {
            if (Get(i, j) != player) {
                rowWin = false;
            }
            if (Get(j, i) != player) {
                colWin = false;
            }
        }
        if (rowWin || colWin) {
            return true;
        }
    }

    bool mainDiagonalWin = true;
    for (int i = 0; i < size_; i++) {
        if (Get(i, i) != player) {
            mainDiagonalWin = false;
        }
    }
    if (mainDiagonalWin) {
        return true;
    }

    bool antiDiagonalWin = true;
    for (int i = 0; i < size_; i++) {
        if (Get(i, size_ - 1 - i) != player) {
            antiDiagonalWin = false;
        }
    }
    return antiDiagonalWin;
}

bool Board::IsFull() const {
    for (int i = 0; i < size_ * size_; i++) {
        if (cells_[i] == Cell::Empty) {
            return false;
        }
    }
    return true;
}

bool Board::operator==(const Board& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (int i = 0; i < size_ * size_; i++) {
        if (cells_[i] != other.cells_[i]) {
            return false;
        }
    }
    return true;
}

bool Board::operator!=(const Board& other) const {
    return !(*this == other);
}

Cell* Board::operator[](int row) {
    return cells_ + row * size_;
}

const Cell* Board::operator[](int row) const {
    return cells_ + row * size_;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    os << board.Size() << std::endl;
    for (int row = 0; row < board.Size(); row++) {
        for (int col = 0; col < board.Size(); col++) {
            Cell value = board.Get(row, col);
            char symbol = '.';
            if (value == Cell::X) symbol = 'X';
            else if (value == Cell::O) symbol = 'O';
            os << symbol << ' ';
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Board& board) {
    int size;
    is >> size;

    Board loaded(size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            char symbol;
            is >> symbol;
            Cell value = Cell::Empty;
            if (symbol == 'X') value = Cell::X;
            else if (symbol == 'O') value = Cell::O;
            loaded.Set(row, col, value);
        }
    }

    board = loaded;
    return is;
}