#include "NBTicTacToe.hpp"

#include <iostream>

#include "TicTacToe.hpp"

namespace {
    bool sameTTT(BoardRef ref, const TicTacToe* ttt) {
        return ref && &ref->get() == ttt;
    }
}

NBTicTacToe::NBTicTacToe() :
    status {},
    nboard {},
    board  ()
{}

void NBTicTacToe::displayBoards() const {
    for (const auto& row : nboard) {
        // This level is every row of boards
        for (const auto& col : row) {
            std::cout << " " << std::string(
                11, sameTTT(board, &col) ? '*' : '-'
            ) << " ";
        }
        std::cout << '\n';
        for (int i = 0; i < BOARDSIZE; i++) {
            // this level is every row of the tictactoe
            for (const auto& col : row) {
                // in here is each tictactoe itself
                col.displayRow(i, sameTTT(board, &col) ? '*' : '|', '|');
            }
            std::cout << "\n";
            if (i != BOARDSIZE - 1) for (const auto& col : row) {
                std::cout
                    << (sameTTT(board, &col) ? '*' : '-')
                    << " -   -   - "
                    << (sameTTT(board, &col) ? '*' : '-');
            }
            std::cout << '\n';
        }
        std::cout << '\n';
        for (const auto& col : row) {
            std::cout << " " << std::string(
                11, sameTTT(board, &col) ? '*' : '-'
            ) << " ";
        }
        std::cout << '\n';
    }
}
