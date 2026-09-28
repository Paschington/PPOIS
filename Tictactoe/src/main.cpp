#include <iostream>
#include "Tictactoe.h"

void PrintBoard(const Board& board) {
    for (int row = 0; row < board.Size(); row++) {
        for (int col = 0; col < board.Size(); col++) {
            Cell value = board.Get(row, col);
            if (value == Cell::X) std::cout << "X ";
            else if (value == Cell::O) std::cout << "O ";
            else std::cout << ". ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int size;
    std::cout << "Enter board size: ";
    std::cin >> size;

    Board board(size);
    Cell currentPlayer = Cell::X;

    while (true) {
        PrintBoard(board);

        int row, col;
        std::cout << "Player " << (currentPlayer == Cell::X ? "X" : "O") << "'s turn (row col): ";
        std::cin >> row >> col;

        if (!board.CanPlace(row, col)) {
            std::cout << "Invalid move, try again." << std::endl;
            continue;
        }
        board.Set(row, col, currentPlayer);

        if (board.HasWinner(currentPlayer)) {
            PrintBoard(board);
            std::cout << "Player " << (currentPlayer == Cell::X ? "X" : "O") << " wins!" << std::endl;
            break;
        }
        if (board.IsFull()) {
            PrintBoard(board);
            std::cout << "It's a draw!" << std::endl;
            break;
        }

        currentPlayer = (currentPlayer == Cell::X) ? Cell::O : Cell::X;
    }
}

