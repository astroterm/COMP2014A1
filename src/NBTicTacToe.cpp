#include "NBTicTacToe.hpp"

#include <iostream>

#include "TicTacToe.hpp"

namespace {
    bool sameTTT(BoardRef ref, TicTacToe* ttt) {
        if (!ref) return false;
        if (&ref.value().get() == ttt) return true;
        return false;
    }
}

NBTicTacToe::NBTicTacToe() :
    status {},
    nboard {},
    board  ()
{}

void NBTicTacToe::displayBoards() const {
    for (const auto& row : nboard) {
        for (int i = 0; i < BOARDSIZE; i++) {
            for (const auto& col : row) {
                col.displayRow(i, '|', '|');
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}
